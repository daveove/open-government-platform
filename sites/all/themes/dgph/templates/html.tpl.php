<?php



/**

 * @file

 * Default theme implementation to display the basic html structure of a single

 * Drupal page.

 *

 * Variables:

 * - $css: An array of CSS files for the current page.

 * - $language: (object) The language the site is being displayed in.

 *   $language->language contains its textual representation.

 *   $language->dir contains the language direction. It will either be 'ltr' or 'rtl'.

 * - $rdf_namespaces: All the RDF namespace prefixes used in the HTML document.

 * - $grddl_profile: A GRDDL profile allowing agents to extract the RDF data.

 * - $head_title: A modified version of the page title, for use in the TITLE

 *   tag.

 * - $head_title_array: (array) An associative array containing the string parts

 *   that were used to generate the $head_title variable, already prepared to be

 *   output as TITLE tag. The key/value pairs may contain one or more of the

 *   following, depending on conditions:

 *   - title: The title of the current page, if any.

 *   - name: The name of the site.

 *   - slogan: The slogan of the site, if any, and if there is no title.

 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and

 *   so on).

 * - $styles: Style tags necessary to import all CSS files for the page.

 * - $scripts: Script tags necessary to load the JavaScript files and settings

 *   for the page.

 * - $page_top: Initial markup from any modules that have altered the

 *   page. This variable should always be output first, before all other dynamic

 *   content.

 * - $page: The rendered page content.

 * - $page_bottom: Final closing markup from any modules that have altered the

 *   page. This variable should always be output last, after all other dynamic

 *   content.

 * - $classes String of classes that can be used to style contextually through

 *   CSS.

 *

 * @see template_preprocess()

 * @see template_preprocess_html()

 * @see template_process()

 */

?>

<!DOCTYPE html>

<!--[if lt IE 7]> <html class="no-js lt-ie9 lt-ie8 lt-ie7" <?php print $html_attributes; ?>> <![endif]-->

<!--[if IE 7]>    <html class="no-js lt-ie9 lt-ie8" <?php print $html_attributes; ?>> <![endif]-->

<!--[if IE 8]>    <html class="no-js lt-ie9" <?php print $html_attributes; ?>> <![endif]-->

<!--[if gt IE 8]><!--> <html <?php print $html_attributes . $rdf_namespaces; ?>> <!--<![endif]-->

<head>

  <?php print $head; ?>

  <title><?php print $head_title; ?></title>

  <?php print $styles; ?>

  <link href='http://fonts.googleapis.com/css?family=Roboto:400,100,300,500,700,900,100italic,300italic,400italic,500italic,700italic,900italic|Roboto+Condensed:300italic,400italic,700italic,400,300,700' rel='stylesheet' type='text/css'>
  <?php print $scripts; ?>

  <!--[if lt IE 9]>

		<script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script>

	<![endif]-->

</head>

<body class="<?php print $classes; ?>" <?php print $attributes;?>>

  <div class="skip-link">

    <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>

  </div>

  <?php print $page_top; ?>

  <?php print $page; ?>

  <?php print $page_bottom; ?>

  <script type="text/javascript" src="https://maps.googleapis.com/maps/api/js"></script>
  <script type="text/javascript" src="//cdnjs.cloudflare.com/ajax/libs/typeahead.js/0.10.4/typeahead.bundle.min.js"></script>
  <script type="text/javascript" src="//cdnjs.cloudflare.com/ajax/libs/chosen/1.4.1/chosen.jquery.min.js"></script>

</body>

</html>

