# Webform Access History
Drupal 7 / BackdropCMS module to track who is looking at webform submissions. 

# To Use
- `Clone` and `drush en webform_access_history`.
- Visit the permissions page
- Set block visibility

Select and set the visibility of the block called *"Webform Access Hisotry, Add Info to Javascript (Main Block)"* some where onto your site. A `Footer` region is suggested. The block itself prints nothing to the site. Instead it initiates the logic need to get the unseen submission ids (`sids`), hand that list to the browser in the `Drupal.settings` object, and include a JavaScript file that will highlight unseen submissions on any webform result page. 

# What's and Why's

## Why a block?
Site builders already know how to control if and where blocks show up on Drupal / BackdropCMS sites. I deicded to keep it familiar. 

## How does it record who has seen which submission
See the function `webform_access_history_webform_submission_load(&$submissions)`. I filter hits from `/node/1/webform-results` and other such paths via 

```
// only react on node/%/submission/% Paths
preg_match('#node/\d+/submission/\d+#', current_path(), $result);
```
## How does it hightlight unseen submissions?
In a JavaScript loop, it finds any reference that links you to a submission and adds an inline style (that can be set from the module's settings page). 

```
jQuery("[href='/node/" + nid+  "/submission/" + sid_number + "']").attr('style', the_style);
```

Feed back and corrections welcomed through [Issue Queue](https://github.com/rgoodie/webform_access_history/issues). License, [GPL 2](https://www.gnu.org/licenses/gpl-2.0.html). Use at your own risk. 
