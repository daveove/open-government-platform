<?php
    global $user;
    $fixedNav = (in_array('editor', $user->roles) || in_array('administrator', $user->roles)) ? '' : ' nav-main-fixed';
?>
<div class="nav-main<?php echo $fixedNav ?>">
  <div id="menu-main" class="row">
    <div class="large-12 columns">
      <nav class="top-bar">
        <ul class="title-area">
          <!-- Title Area -->
          <li class="name">
            <h1> <a href="#"></a> </h1>
          </li>
          <li class="toggle-topbar menu-icon"><a href="#"><span>Menu</span></a></li>
        </ul>
        <section class="top-bar-section">
          <!-- Left Nav Section -->
          <ul class="left">
            <li class="divider"></li>
            <li id="#"><?php print l('About', 'node/2'); ?></li>
            <li class="divider"></li>
            <li id="#"><?php print l('News', 'node/33'); ?></li>
            <li class="divider"></li>
            <li id="#"><?php print l('Data', 'catalogue'); ?></li>
            <li class="divider"></li>
            <li id="#"><?php print l('Infographics', 'node/24'); ?></li>
            <li class="divider"></li>
            <li id="#"><?php print l('Apps', 'node/22'); ?></li>
            <li class="divider"></li>
            <li id="#"><?php print l('Community', 'node/6'); ?></li>
            <li class="divider"></li>
            <li id="#"><?php print l('Contact', 'contact-us'); ?></li>
          </ul>
          <!-- Right Nav Section -->
          <ul class="right">
		    <li class="divider"></li>
            <li class="search">
				<form id="search-form" class="search-form" accept-charset="UTF-8" method="get" action="/catalogue/dataset">
				<div class="search topseacrh"><input id="edit-keys" name="q" type="search" class="sitesearch-box"></div>
				</form>
            </li>
            <li class="divider"></li>
          </ul>
        </section>
      </nav>
    </div>
  </div>
</div>

<div id="header-new">
   <header class="row">
   <div class="large-12 columns">
      <div class="left-column">
		<div class="logo-area">
		  <?php if ($logo): ?>	
			<a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
				<img class="adaptive-image" src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
			</a>
		  <?php endif; ?>
		 </div>
	  </div><!-- Logo Area Columns-->

      <div class="right-column">
		<div class="login-profile">
			<?php print login_profile(); ?>
		</div>
	  </div><!-- Header Right Columns-->
   </div>
   </header>
</div><!-- header-new -->


<?php
$urlalias = explode('/',drupal_get_path_alias());
$firsturl = '';
if(sizeof($urlalias) > 1){
	$firsturl = $urlalias[0];
}

/* About us  */
if(arg(0)=='node' && arg(1)==2){
	$firsturl = 'activity';
}
/* Contact us  */
if(arg(0)=='contact-us'){
	$firsturl = 'activity';
}
/* news/latest  */
if(arg(0)=='node' && arg(1)==33){
	$firsturl = 'activity';
}

?>

<?php $activity = true; if(arg(0)=='testimonials' || arg(0)=='activity' || arg(0)=='latest-visualizations' || $firsturl=='activity' || $firsturl=='testimonials' || $firsturl=='visualizations') : $activity = false; ?>
<div id="maindiv" class="<?php print arg(0).arg(1); ?>">
	<div class="row">
	  <?php if ($messages): print $messages; endif; ?>

	  <div id="main" class="large-12 columns">
		<?php if (!empty($page['highlighted'])): ?>
		  <div class="highlight panel callout">
			<?php print render($page['highlighted']); ?>
		  </div>
		<?php endif; ?>
		<a id="main-content"></a>
		<?php if ($title): ?>
		  <?php print render($title_prefix); ?>
		  <h1 id="page-title" class="title <?php print arg(0).arg(1); ?>"><?php print $title; ?></h1>
		  <?php print render($title_suffix); ?>
		<?php endif; ?>

		<?php if (!empty($tabs)): ?>
		  <?php print render($tabs); ?>
		  <?php if (!empty($tabs2)): print render($tabs2); endif; ?>
		<?php endif; ?>
		<?php if ($action_links): ?>
		  <ul class="action-links">
			<?php print render($action_links); ?>
		  </ul>
		<?php endif; ?>
		<?php print render($page['content']); ?>
	  </div>
	</div><!-- Content Area -->
</div><!-- Main Div -->
<?php endif; ?>
	

<?php if($activity) : ?>
<?php
    if (!empty($messages)) {
        print "<div class='row'><div class='clear'></div>$messages</div>"; 
    }
?>
<?php print render($page['content']); ?>
<?php endif; ?>

<?php $themePath = DRUPAL_ROOT.base_path().drupal_get_path('theme', 'dgph'); ?>
<?php include $themePath."/templates/include/footer.php" ?>