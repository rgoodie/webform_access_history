<?php
/**
 * Created by PhpStorm.
 * User: carbon
 * Date: 10/21/16
 * Time: 2:56 PM
 */

function _webform_access_history_ajax_process($sid) {

    $logged_in = $GLOBALS['user'];

    require_once(drupal_get_path('module', 'webform') . '/includes/webform.submissions.inc');
    $submission = webform_get_submissions(array( 'sid' => $sid));
    // dpm($submission);

    $recording_result = _webform_access_history_do_recording(
        $logged_in->uid,
        $submission[$sid]->uid,
        $submission[$sid]->sid,
        $submission[$sid]->nid
    );

    drupal_json_output(array(
       'result'=>$recording_result
    ));



}