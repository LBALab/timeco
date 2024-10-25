---
title: Tools
layout: home
parent: Gallery
nav_order: 8
permalink: /gallery/tools
images:
- image_path: assets/images/tools/tced_farwest_old_scan.jpg
  title: TCED Farwest Old Scan
  link: assets/images/tools/tced_farwest_old_scan.jpg
- image_path: assets/images/tools/tced_1.png
  title: TCED 1
  link: assets/images/tools/tced_1.png
- image_path: assets/images/tools/tced_2.png
  title: TCED 2
  link: assets/images/tools/tced_2.png
- image_path: assets/images/tools/adeline_palette.png
  title: Adeline Palette
  link: assets/images/tools/adeline_palette.png
- image_path: assets/images/tools/mini_draw_ui.png
  title: Mini Draw UI
  link: assets/images/tools/mini_draw_ui.png
- image_path: assets/images/tools/modeleditor_1.png
  title: Model Editor 1
  link: assets/images/tools/modeleditor_1.png
- image_path: assets/images/tools/modeleditor_2.png
  title: Model Editor 2
  link: assets/images/tools/modeleditor_2.png
- image_path: assets/images/tools/modeleditor_3.png
  title: Model Editor 3
  link: assets/images/tools/modeleditor_3.png
- image_path: assets/images/tools/modeleditor_4.png
  title: Model Editor 4
  link: assets/images/tools/modeleditor_4.png
- image_path: assets/images/tools/lba2-animations.jpg
  title: LBA2 Animations
  link: assets/images/tools/lba2-animations.jpg
- image_path: assets/images/tools/credits_1.png
  title: Credits 1
  link: assets/images/tools/credits_1.png
- image_path: assets/images/tools/credits_2.png 
  title: Credits 2
  link: assets/images/tools/credits_2.png
- image_path: assets/images/tools/credits_3.png 
  title: Credits 3
  link: assets/images/tools/credits_3.png
- image_path: assets/images/tools/credits_4.png 
  title: Credits 4
  link: assets/images/tools/credits_4.png 
- image_path: assets/images/tools/credits_5.png 
  title: Credits 5
  link: assets/images/tools/credits_5.png
- image_path: assets/images/tools/level_list.png
  title: Level List
  link: assets/images/tools/level_list.png
- image_path: assets/images/tools/lib_menu_text_mode.png
  title: Lib Menu Text Mode
  link: assets/images/tools/lib_menu_text_mode.png
- image_path: assets/images/tools/make_hqr_exe.png
  title: Make HQR Exe
  link: assets/images/tools/make_hqr_exe.png
---

# Tools

<div>
    {% for image in page.images %}
        <a href="{{ site.baseurl }}/{{ image.link }}" style="margin: 6px; display: inline-flex; border-radius: 15px; border: 1px solid #80808042; padding: 5px;">
            <img src="{{ site.baseurl }}/{{ image.image_path }}" alt="{{ image.title}}" style="border-radius: 10px" />
        </a>
    {% endfor %}
</div>

Partial Source: [https://blog.defence-force.org/?tag=Time%20Commando](https://blog.defence-force.org/?tag=Time%20Commando)
