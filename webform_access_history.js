/**
 * Created by carbon on 10/14/16.
 */

// wait until jQ is ready.
jQuery(function () {

    console.log('webform_access_history enabled');


    // wait until the object is created
    jQuery(Drupal.settings.webforms_access_history).ready(function () {


        // this NID
        var nid = Drupal.settings.webforms_access_history_guessed_nid;

        // the style (from Drupal settings)
        var the_style = Drupal.settings.webforms_access_history_style

        // loop through, find <a> tag and add class
        for (var index in Drupal.settings.webforms_access_history) {
            var sid_number = Drupal.settings.webforms_access_history[index];
            jQuery("[href$='node/" + nid + "/submission/" + sid_number + "']").closest('tr').attr('style', the_style);
        }


    });


})


/*
 * Click bind for ajax tracking
 */
jQuery('tr').click(function() {
    var self = jQuery(this);
    var this_href = self.find('a').attr('href');
    var sid = this_href.split("/").pop();
    console.log(sid);
    self.attr('style','');


    jQuery.ajax('?q=webform/access/ajax/' + sid, function (data, status) {
        console.log(data);











    })
});

