<?php if ($page['main_menu'] || $page['search_area']): ?>
<div id="header-top">
   <div class="row">
	   <?php if ($page['main_menu']): ?>
		  <nav class="nine columns">
			<?php print render($page['main_menu']); ?>
		  </nav><!-- Menu Area -->
	   <?php endif; ?>

	   <?php if ($page['search_area']): ?>
		  <div class="three columns">
			<?php print render($page['search_area']); ?>
		  </div><!-- Search Area -->
	   <?php endif; ?>
   </div>
</div><!-- Header Top -->
<?php endif; ?>

<div id="header">
   <header class="row">
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
   </header>
</div><!-- Header -->

<?php if ($page['show_case']): ?>
  <div id="showcase">
	<div class="row">
		<div class="twelve columns">
			<?php print render($page['show_case']); ?>
		</div>
	</div>
  </div><!-- Showcase -->
<?php endif; ?>

<div id="maindiv" class="<?php print arg(0).arg(1); ?>">
	<div class="row">
	  <?php if ($messages): print $messages; endif; ?>

	  <div id="main" class="<?php print $main_grid; ?> columns">
		<?php if (!empty($page['highlighted'])): ?>
		  <div class="highlight panel callout">
			<?php print render($page['highlighted']); ?>
		  </div>
		<?php endif; ?>
		<a id="main-content"></a>
		<?php if ($title && !$is_front): ?>
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
	  <?php if (!empty($page['sidebar_first'])): ?>
		<div id="sidebar-first" class="<?php print $sidebar_first_grid; ?> columns sidebar">
		  <?php print render($page['sidebar_first']); ?>
		</div>
	  <?php endif; ?>
	  <?php if (!empty($page['sidebar_second'])): ?>
		<div id="sidebar-second" class="<?php print $sidebar_sec_grid;?> columns sidebar">
		  <?php print render($page['sidebar_second']); ?>
		</div>
	  <?php endif; ?>
	</div><!-- Content Area -->
</div><!-- Main Div -->


<?php if ($page['footer_first'] || $page['footer_middle'] || $page['footer_last']): ?>
<div class="footer">
    <footer class='row foot-nav'>
        <?php if ($page['footer_first']): ?>
           <div class="four columns">
             <?php print render($page['footer_first']); ?>
           </div>
        <?php endif; ?>
        <?php if ($page['footer_middle']): ?>
           <div class="four columns">
             <?php print render($page['footer_middle']); ?>
           </div>
        <?php endif; ?>
        <?php if ($page['footer_last']): ?>
           <div class="four columns">
             <?php print render($page['footer_last']); ?>
           </div>
        <?php endif; ?>
    </footer>
</div><!-- Footer -->
<?php endif; ?>