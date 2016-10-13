<?php

function webform_access_history_housekeeping_reset() {

    webform_access_history_uninstall();
    _webform_access_history_firstrun();

    return drupal_set_message('Resetting table');

}