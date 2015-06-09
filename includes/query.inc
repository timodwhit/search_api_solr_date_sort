<?php
/**
 * @file
 * Contains SearchApiViewsQuery.
 */

/**
 * Base extension to override the sorting to allow for the date to sort.
 */
class SearchApiSolrDateSortQuery extends SearchApiQuery  {

  /**
   * {@inheritdoc}
   */
  // Largely copied from SearchApiQuery but adds handling for date string
  public function sort($field, $order = 'ASC') {
    $fields = $this->index->options['fields'];
    $fields += array(
      'search_api_relevance' => array('type' => 'decimal'),
      'search_api_id' => array('type' => 'integer'),
      'search_api_random' => array('type' => 'integer'),
    );
    // Add Date Handling for the sort.
    $date_fields = array();
    foreach ($fields as $k => $v) {
      // If a date field, process the name into the defined string.
      if ($v['type'] == 'list<date>') {
        $date_fields[search_api_solr_date_sort_to_string($k)] = array('type' => 'date');
      }
    }
    $fields += $date_fields;

    if (empty($fields[$field])) {
      throw new SearchApiException(t('Trying to sort on unknown field @field.', array('@field' => $field)));
    }
    $type = $fields[$field]['type'];
    // Add the check to make sure the list<date> isn't include, but other lists are excluded.
    if ($type != 'list<date>' && (search_api_is_list_type($type) || search_api_is_text_type($type))) {
      throw new SearchApiException(t('Trying to sort on field @field of illegal type @type.', array('@field' => $field, '@type' => $type)));
    }
    if ($field != 'search_api_random') {
      $order = strtoupper(trim($order)) == 'DESC' ? 'DESC' : 'ASC';
    }
    else {
      if ($order == 'ASC' || $order == "DESC") {
        $order = 'random_' . rand(1,200) . ' asc';
      }
    }
    $this->sort[$field] = $order;
    return $this;
  }

}
