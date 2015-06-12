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
<!-- masthead -->
<div id="masthead">
  <div class="row">
    <div id="logo" class="large-6 columns">
		<?php if ($logo): ?>	
		<a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
			<img class="adaptive-image" src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
		</a>
		<?php endif; ?>
    </div>
    <div class="large-3 columns"></div>
    <div class="large-3 columns">
		<div class="login-profile">
			<?php print login_profile(); ?>
		</div>
	</div>
  </div>
</div>
<!-- banner -->
<div id="banner-container">
  <div class="row">
    <div class="large-12 columns">
      <div id="banner-content" class="row">
        <div id="banner" class="large-9 columns">
          <ul data-orbit data-options="bullets:false;">
            <li> <img src="/sites/all/themes/dgph/images/image-slider-1.jpg">
              <div class="orbit-caption">
                <h3>Amet Ligula Nullam Sit Consectetur</h3>
                <p>Maecenas faucibus mollis interdum. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</p>
              </div>
            </li>
            <li> <img src="/sites/all/themes/dgph/images/image-slider-2.jpg">
              <div class="orbit-caption">
                <h3>Elit Pellentesque Tellus Venenatis Justo</h3>
                <p>Maecenas sed diam eget risus varius blandit sit amet non magna. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</p>
              </div>
            </li>
            <li> <img src="/sites/all/themes/dgph/images/image-slider-3.jpg">
              <div class="orbit-caption">
                <h3>Ridiculus Parturient Sollicitudin Cursus Bibendum</h3>
                <p>Maecenas faucibus mollis interdum. Morbi leo risus, porta ac consectetur ac, vestibulum at eros.</p>
              </div>
            </li>
          </ul>
        </div>
        <div id="search-tool" class="large-3 columns">

			<div class="search-home">
			  <div class="search-home-con"><br />
				<h2>Search Data</h2>
				<div class="search-area">
				  <input type="image" class="clander-btn" src="/sites/all/themes/dgph/images/clander-icon.png" name="">
				  <input type="text" class="clander-search" name="">
				</div>	
				<div class='search-button'><br />
				  <input name="search" type="button" value="Search" class="search-button">
				</div>
			  </div>
			</div>

		</div>
      </div>
    </div>
  </div>
</div>
<!-- featured content -->
<div id="featured-container">
  <div class="row">
    <div class="large-12 columns">
      <div id="featured-box" class="row">
        <div class="large-12 columns">
          <h2>Featured Infographics</h2>
        </div>
        <div class="large-4 columns">
          <h3><a href='/infographics'>Data 01</a></h3>
          <a href='/infographics'><img src="/sites/all/themes/dgph/images/img-1.png"></a>
          <p>Aenean lacinia bibendum nulla sed consectetur. Integer posuere erat a ante venenatis dapibus posuere velit aliquet. Curabitur blandit tempus porttitor.</p>
        </div>
        <div class="large-4 columns">
          <h3><a href='/infographics'>Data 02</a></h3>
          <a href='/infographics'><img src="/sites/all/themes/dgph/images/img-2.png"></a>
          <p>Maecenas faucibus mollis interdum. Nullam id dolor id nibh ultricies vehicula ut id elit. Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p>
        </div>
        <div class="large-4 columns">
          <h3><a href='/infographics'>Data 03</a></h3>
          <a href='/infographics'><img src="/sites/all/themes/dgph/images/img-3.png"></a>
          <p>Fusce dapibus, tellus ac cursus commodo, tortor mauris condimentum nibh, ut fermentum massa justo sit amet risus. Vestibulum id ligula porta felis euismod semper. Nulla vitae elit libero, a pharetra augue.</p>
        </div>
      </div>
    </div>
  </div>
</div>
<!-- content -->
<div id="content-main">
  <div class="row community-row">
    <div class="large-6 columns">
      <div class="flex-video conntent-area activities">
            <h1>Activities</h1>
            <img src="/sites/all/themes/dgph/images/acctivity.png" alt="">
            <h2>Duis autem vel eum iriure dolor</h2>
            <p>Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat. 
    Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel </p>
            <div class="view">
                    <a href="#" style="float:left;">View All</a>
            </div>
      </div>
    </div>
    <div class="large-3 columns conntent-area latestnews">
      <h1>Latest News</h1>
        <?php
		// load latest news
		$query = db_select('node', 'n')
				->fields('n', array('nid'))
				->condition('n.type', 'blog')
				->condition('n.status', 1)
				->orderBy('n.created', 'desc')
				->range(0, 3);
		$nids = $query->execute()->fetchCol();
		$latestNews = node_load_multiple($nids);

            $idx = 0;
            while(!empty($latestNews) && $idx<3) {
                $entry = array_shift($latestNews);
                $title = $entry->title;
                $text = $entry->body['und'][0]['value'];
                if (strlen($text)>75) {
                    $text = substr($text, 0, 75) . '...';
                }
                $dt = date('M j, Y', $entry->created);
                $last = (($idx>0) && (0==(($idx+1)%3))) ? ' post-last' : '';
        ?>
        <div class="post<?php echo $last ?>">
            <h2><?php echo $title ?></h2>
            <h3><?php echo $dt.'<br>'.$entry->name ?></h3>
            <?php echo  $text ?>
        </div>
        <?php 
                $idx++;
            } 
        ?>
        <div class="view">
            <a href="/news/latest" style="float:left;">View All</a>
        </div>

    </div>
    <div class="large-3 columns conntent-area latestdata">
        <h1>Latest Data</h1>
        <?php
            $block = module_invoke('dgph_content', 'block_view', 'dgph_content_latest_datasets');
            print render($block['content']);
        ?>
        <div class="view">
            <a href="/catalogue" style="float:left">View All</a>
        </div>
    </div>
  </div>
</div>
<!-- start aux footer -->
<div class="footer-aux1 footer-section">
  <div class="row">
    <div class="large-6 columns">
      <h6>About data.gov.ph</h6>
      <p>Maecenas faucibus mollis interdum. Etiam porta sem malesuada magna mollis euismod. Cras justo odio, dapibus ac facilisis in, egestas eget quam. Fusce dapibus, tellus ac cursus commodo, tortor mauris condimentum nibh, ut fermentum massa justo sit amet risus. Praesent commodo cursus magna, vel scelerisque nisl consectetur et. Duis mollis, est non commodo luctus, nisi erat porttitor ligula, eget lacinia odio sem nec elit. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus.</p>
    </div>
    <div class="large-3 columns">
      <h6>heading</h6>
      <p>content</p>
    </div>
    <div class="large-3 columns">
      <h6>heading</h6>
      <p>content</p>
    </div>
  </div>
</div>
<!-- end aux footer -->

<?php $themePath = DRUPAL_ROOT.base_path().drupal_get_path('theme', 'dgph'); ?>
<?php require $themePath."/templates/include/footer.php" ?>

