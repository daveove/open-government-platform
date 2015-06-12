<?php
    /**
     * Build the traffic visualization interface
     */
    function dgph_infographics_traffic_visualization() {
        return theme('dgph_infographics_traffic_visualization');
    }
    /**
     * Theme for traffic visualization interface
     */
    function theme_dgph_infographics_traffic_visualization(&$vars) {
        $modPath = drupal_get_path('module', 'dgph_infographics');
        drupal_add_css($modPath.'/include/traffic/leaflet/leaflet.css', array('group'=>CSS_THEME, 'weight'=>999));
        drupal_add_css($modPath.'/include/traffic/css/traffic.css', array('group'=>CSS_THEME, 'weight'=>1000));
        drupal_add_js($modPath.'/include/traffic/leaflet/leaflet.js');
        drupal_add_js($modPath.'/include/traffic/js/layer-json.js');
        drupal_add_js($modPath.'/include/traffic/js/traffic.js');
        drupal_set_title('Infographics - Traffic Alert Visualization');
        $code = "
                   <div class='row header'>
                        <div class='large-12 columns'>
                            <div class='row'>
                                <div class='large-6 columns'>
                                    <p>The Development Authority have been testing an open-source platform for recording and communicating real-time accident, road closure, event, and faulty traffic signal information. These agencies would like to experiment by making the public data feeds available to developers.</p>
                                    <p>Because these data are geographically referenced can now create data visualizations to see where the most accidents occur over time  and at what time of day and during what kind of weather conditions.</p>
                                </div>
                                <div class='large-6 columns'>
                                    <p>These analyses would support more efficient assignment of traffic to prevent accidents, identify priority investment needs, and support budget proposals for improvements. Also, these data, in real time, transit operators, and identifying routes to avoid.</p>
                                    <p>The Task Force in partnership with Insomniac Design have been experimenting with a sample of the data provided by Government and the to find the best ways to communicate these information to the public and to create tools to support the analysis of historical data.</p>
                                </div>
                            </div>
                        </div>
                    </div>
                    <div id='map'></div>
                    <div class='row footer'>
                        <div class='large-1 columns'></div>
                        <div class='large-10 columns'><h1>Source: Location</h1></div>
                        <div class='large-1 columns'></div>
                    </div>
                    <div class='row footer footer-last'>
                        <div class='large-12 columns'>
                            <div class='row'>
                                <div class='large-6 columns'>
                                    <p>The Traffic System unifies several widely-available software packages to create its unique approach to showcasing transportation around. Showcasing current traffic conditions provides an immediate use of the information while the map tracks and visualizes data over time, allowing a user to discover trends and identify areas requiring adjustements.</p> 
                                    <p>The muted presence of the map is created using MapBox layers and enhanced by incorporating the advanced street mapping components of OpenStreetMap. A subdued, limited color palette creates a higher focus on the alerts and content.</p>
                                </div>
                                <div class='large-6 columns'>
                                    <p>Transparent dots indicate areas that incidents have occurred and allow a user to interact while still being able to easily discern exact locations. Other traffic-related concerns are indicated by iconography and color.</p>
                                    <p>The interactive features of the map draw on a live database which outputs historical and current data that is translated which creates the unique style of visualizations that populate the map.</p>
                                </div>
                            </div>
                        </div>
                    </div>";
        return $code;
   }
?>