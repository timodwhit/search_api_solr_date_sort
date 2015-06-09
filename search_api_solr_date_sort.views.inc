<?php
/**
 * @file
 * Views file for search_api_solr_date_sort.
 */

/**
 * Implementation of hook_views_plugins().
 */
function search_api_solr_date_sort_views_plugins() {

  $plugins['query']['search_api_solr_date_sort_views_query'] = array(
    'title' => t('Search API Solr Date Sort Views Query'),
    'help' => t('Query will be generated and ran through using a custom query to allow sorting by date.'),
    'handler' => 'SearchApiSolrDateSortViewsQuery',
    'parent' => 'search_api_views_query',
  );

  return $plugins;
}


