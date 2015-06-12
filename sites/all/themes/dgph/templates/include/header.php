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
            <h1> <a href="/"> gov.ph </a> </h1>
          </li>
          <li class="toggle-topbar menu-icon"><a href="#"><span>Menu</span></a></li>
        </ul>
        <section class="top-bar-section">
          <!-- Left Nav Section -->
          <ul class="left">
            <li class="divider"></li>
            <li id="#"><a href="/about">About</a></li>
            <li class="divider"></li>
            <li id="#"><a href="/news/latest">News</a></li>
            <li class="divider"></li>
            <li id="#"><a href="/catalogue">Data</a></li>
            <li class="divider"></li>
            <li id="#"><a href="/infographics">Infographics</a></li>
            <li class="divider"></li>
            <!--<li id="#"><a href="/node/9">Requests</a></li>
            <li class="divider"></li>-->
            <li id="#"><a href="/apps">Apps</a></li>
          </ul>
          <!-- Right Nav Section -->
          <ul class="right">
            <li class="divider"></li>
            <li id="#"><a href="/community">Community</a></li>
            <li class="divider"></li>
            <li id="#"><a href="/contact-us">Contact</a></li>
            <li class="divider"></li>
            <li class="search">
			   <?php if ($page['search_area']): ?>
					<?php print render($page['search_area']); ?>
			   <?php endif; ?>
            </li>
            <li class="divider"></li>
          </ul>
        </section>
      </nav>
    </div>
  </div>
</div>