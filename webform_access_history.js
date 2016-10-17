/**
 * Created by carbon on 10/14/16.
 */

// wait until jQ is ready.
jQuery(function() {


    // wait until the object is created
    jQuery(Drupal.settings.webforms_access_history).ready(function() {


        // this NID
        var nid = Drupal.settings.webforms_access_history_guessed_nid;

        // the style (from Drupal settings)
        var the_style = Drupal.settings.webforms_access_history_style

        // loop through, find <a> tag and add class
        for (var index in Drupal.settings.webforms_access_history) {
            var sid_number =Drupal.settings.webforms_access_history[index];
            jQuery("[href='/node/" + nid+  "/submission/" + sid_number + "']").attr('style', the_style);
        }


    });



})

