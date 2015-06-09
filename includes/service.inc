<?php
/**
 * @file
 * Contains SearchApiViewsEventsSolrService.
 */

/**
 * Extension class with generic implementation of most service methods.
 */
class SearchApiSolrDateSortSolrService extends SearchApiSolrService {

  /**
   * {@inheritdoc}
   */
  public function query(SearchApiIndex $index, $options = array()) {
    // To Override the sort, we need to instantiate a different method.
    return new SearchApiSolrDateSortQuery($index, $options);
  }

}

