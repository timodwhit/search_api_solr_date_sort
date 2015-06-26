INTRODUCTION
------------
Search API Solr Date Sort adds the ability to sort the search api solr results by date.
This is advantageous for quite a few reasons.

REQUIREMENTS
------------
This module requires search_api_solr.


INSTALLATION
------------
 * Install as you would normally install a contributed Drupal module. See:
   https://drupal.org/documentation/install/modules-themes/modules-7
   for further information.


CONFIGURATION
-------------
 * No configuration is needed. This will add a sort option to your views, if you
   would like to use that. The module however does require a re-indexing.


FAQ
---
Q: How does the date sort work?

A: Date sort works by breaking each date out as a single instance in the solr index.
   This allows sort to happen but runs the risk of a repeating event to show multiple times.


MAINTAINERS
-----------
Current maintainers:
 * Tim Whitney (timodwhit) - https://www.drupal.org/user/1629156


This project has been sponsored by:
 * Miles
 Visit https://milespartnership.com
