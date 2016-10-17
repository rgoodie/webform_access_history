<?php




function webform_access_history_options() {

    $form = array();

    $form['wah_selected_style'] = array(
        '#type'=>'textarea',
        '#value'=>variable_get('wah_selected_style', WAH_DEFAULT_HIGHLIGHT_CSS),
        '#title'=>t('CSS style for "New" submissions '),
        '#description'=>t('Please use valid CSS syntax.'),
    );


    return system_settings_form($form);



}