<?php


function webform_access_history_options() {

    $form = array();

    $form['wah_selected_style'] = array(
        '#type'=>'textarea',
        '#default_value'=>variable_get('wah_selected_style'),
        '#title'=>t('CSS style for "New" submissions '),
    );


    return system_settings_form($form);



}