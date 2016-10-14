<?php


function webform_access_history_jsObject()
{
    // TODO: add js embed

    // enforce permission!
    if (!_webform_access_history_enforce_permission()) {
        return;
    }


    drupal_add_js(array('webforms_access_history' => array(
        'testing' => true,
    )), 'setting');
    return 'test';
}


/**
 * Produces a table of all histories.
 * @param int $filter_by_uid
 * @return Table
 */
function webform_access_history_report($filter_by_uid = 0)
{

    // enforce permission!
    if (!_webform_access_history_enforce_permission()) {
        return;
    }

    // No filter, get everybody
    if ($filter_by_uid == 0) {
        $result = db_select(WAH_TABLE_NAME, 'w')
            ->fields('w')
            ->orderBy('timestamp')
            ->execute();
    }

    // filter query by a single VIEWER UID
    else {
        $result = db_select(WAH_TABLE_NAME, 'w')
            ->fields('w')
            ->orderBy('timestamp')
            ->condition('logged_in_uid', $GLOBALS['user']->uid, '=')
            ->execute();
    }

    return webform_access_history_formatTable($result);
}

function webform_access_history_new($filter_by_uid = 0)
{

    // enforce permission!
    if (!_webform_access_history_enforce_permission()) {
        return;
    }

    $new_sids = webform_access_history_new_query($filter_by_uid);
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

/**
 * @param $result of the query
 * @return Table or String.
 */
function webform_access_history_formatTable($result)
{

    $user_id_array = array();
    $submission_array = array();
    $out_bound = array();
    $index = 0;
    while ($record = $result->fetchAssoc()) {

        // ids to get other elements
        $user_id_array[] = $record['logged_in_uid'];
        $user_id_array[] = $record['submitted_uid'];

        $out_bound[$index] = $record;
        $index++;
    }


    // build user array once. If put into loop, that's crazy on the processor.
    $user_array = user_load_multiple(array_unique($user_id_array));


    // Pretty up dataset with another loop
    foreach ($out_bound as $k => $v) {

        // Viewer Name
        $out_bound[$k]['Viewer Name'] = $user_array[$v['logged_in_uid']]->name;

        // SUbmiiter Name
        $out_bound[$k]['Submitter Name'] = $user_array[$v['submitted_uid']]->name;

        // Time Stamp
        $out_bound[$k]['Time Stamp'] = format_date($out_bound[$k]['timestamp']);

        // Form link
        $out_bound[$k]['Webform Link'] = l(t('Form'), sprintf(
            "/node/%d",
            $v['nid']
        ));

        // Submission Link
        $out_bound[$k]['Submission Link'] = l(t('Submission'), sprintf(
            "/node/%d/submission/%d",
            $v['nid'],
            $v['sid']
        ));


        // remove unpretty columns for display
        unset($out_bound[$k]['logged_in_uid']);
        unset($out_bound[$k]['submitted_uid']);
        unset($out_bound[$k]['uid']);
        unset($out_bound[$k]['sid']);
        unset($out_bound[$k]['nid']);
        unset($out_bound[$k]['timestamp']);


    }


    // if we have a postitive count, return table.
    if (count($out_bound) > 0) {
        return theme_table(array(
            'header' => array_keys($out_bound[0]),
            'rows' => $out_bound,
            'attributes' => array('style' => 'width: 100%;'),
            'caption' => '',
            'colgroups' => array(),
            'sticky' => '',
            'empty' => ''
        ));
    } // else, just a null message
    else {
        return 'No results';
    }
}