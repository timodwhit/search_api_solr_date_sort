<?php
/**
 * @file
 * Contains SearchApiViewsQuery.
 */

/**
 * Views query class using a Search API index as the data source.
 */
class SearchApiSolrDateSortViewsQuery extends SearchApiViewsQuery {

  /**
   * @inheritdoc
   *
   * This method is largely copied from the SearchApiViewsQuery::get_results_wrappers.
   * However, this method strips handles the unique ids if there are more than 1
   * document per node.
   */
  public function get_result_wrappers($results, $relationship = NULL, $field = NULL) {
    $entity_type = $this->index->getEntityType();
    $wrappers = array();
    $load_entities = array();
    foreach ($results as $row_index => $row) {
      $entity_id = $row->entity;
      // Remove the appended: -### to use as entity_id.
      $hyphen = strpos($entity_id, "-");
      if (!empty($hyphen)) {
        $entity_id = substr($row->entity, 0, $hyphen);
      }

      if ($entity_type && isset($row->entity)) {
        // If this entity isn't load, register it for pre-loading.
        if (!is_object($row->entity)) {
          $load_entities[$row->entity] = $row_index;
        }
        $wrappers[$row_index] = $this->index->entityWrapper($entity_id);
      }
    }

    // If the results are entities, we pre-load them to make use of a multiple
    // load. (Otherwise, each result would be loaded individually.)
    if (!empty($load_entities)) {
      $entities = entity_load($entity_type, array_keys($load_entities));
      foreach ($entities as $entity_id => $entity) {
        $wrappers[$load_entities[$entity_id]] = $this->index->entityWrapper($entity);
      }
    }

    // Apply the relationship, if necessary.
    $type = $entity_type ? $entity_type : $this->index->item_type;
    $selector_suffix = '';
    if ($field && ($pos = strrpos($field, ':'))) {
      $selector_suffix = substr($field, 0, $pos);
    }
    if ($selector_suffix || ($relationship && !empty($this->view->relationship[$relationship]))) {
      // Use EntityFieldHandlerHelper to compute the correct data selector for
      // the relationship.
      $handler = (object) array(
        'view' => $this->view,
        'relationship' => $relationship,
        'real_field' => '',
      );
      $selector = EntityFieldHandlerHelper::construct_property_selector($handler);
      $selector .= ($selector ? ':' : '') . $selector_suffix;
      list($type, $wrappers) = EntityFieldHandlerHelper::extract_property_multiple($wrappers, $selector);
    }
    return array($type, $wrappers);
  }

}
