<?php

/**
 *
 * One of the work horses of the function. This block if included will highlight the node submissions
 * the current logged in user has not yet seen.
 *
 * @return string|void
 */
function webform_access_history_jsObject()
{

    // enforce permission!
    if (!_webform_access_history_enforce_permission()) {
        return;
    }

    // Match. If this doesn't match path, exit.
    preg_match('#node/(\d+)/webform-results#', current_path(), $m);
    if (!count($m) ) {
        return;
    };
    $nid_from_match = $m[1];

    // Ensure what we think is the node ID is a number. If not
    // something is wrong. Logic will be askew. Exit here.
    if (!is_numeric($nid_from_match)) {
        return;
    }

    // Make the browser aware of our important numbers.
    drupal_add_js(array('webforms_access_history' => webform_access_history_new_query($nid_from_match)), 'setting');
    drupal_add_js(array('webforms_access_history_guessed_nid' => $nid_from_match), 'setting');

    // Throw over CSS class
    drupal_add_js(array('webforms_access_history_style'=>variable_get('wah_selected_style', WAH_DEFAULT_HIGHLIGHT_CSS)), 'setting');

    drupal_add_js(drupal_get_path('module', 'webform_access_history') . '/webform_access_history.js', array(
        'scope'=>'footer',
        'weight'=>-1000
    ));
    return '<!-- webform_access_history JavaScript object loaded -->';
}





function webform_access_history_new_query($uid)
{

    // Get all submissions
    $all_sids = array();
    $all_sids_result = db_select('webform_submissions', 'ws')
        ->distinct()
        ->fields('ws', array('sid'))
        ->orderby('ws.sid')
        ->execute()
        ->fetchAllAssoc('sid');
    foreach ($all_sids_result as $sid) {
        $all_sids[] = $sid->sid;
    }
    $all_sids = array_unique($all_sids);

    // Get sid that this user has seen
    $my_sids_result = db_select(WAH_TABLE_NAME, 'w')
        ->fields('w', array('sid'))
        ->orderBy('timestamp')
        ->condition('logged_in_uid', $GLOBALS['user']->uid, '=')
        ->execute()
        ->fetchAll();

    $my_sids = array();
    foreach ($my_sids_result as $mysid) {
        $my_sids[] = $mysid->sid;
    }
    $my_sids = array_unique($my_sids);

    // return the diffs
    return array_diff($all_sids, $my_sids);

}
