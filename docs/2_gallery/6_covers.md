---
title: Covers
layout: home
parent: Gallery
nav_order: 6
permalink: /gallery/covers
images:
- image_path: assets/images/covers/jewel_case_booklet_front.jpg
  title: Jewel Case Booklet Front
  link: assets/images/covers/jewel_case_booklet_front.jpg
- image_path: assets/images/covers/jewel_case_booklet_back.jpg
  title: Jewel Case Booklet Back
  link: assets/images/covers/jewel_case_booklet_back.jpg
- image_path: assets/images/covers/jewel_case_inlay_front.jpg
  title: Jewel Case Inlay Front
  link: assets/images/covers/jewel_case_inlay_front.jpg
- image_path: assets/images/covers/jewel_case_inlay_back.jpg
  title: Jewel Case Inlay Back
  link: assets/images/covers/jewel_case_inlay_back.jpg
- image_path: assets/images/covers/usa_release_box_front.jpg
  title: USA Release Box Front
  link: assets/images/covers/usa_release_box_front.jpg
- image_path: assets/images/covers/usa_release_box_back.jpg
  title: USA Release Box Back
  link: assets/images/covers/usa_release_box_back.jpg
- image_path: assets/images/covers/usa_release_cd.jpg
  title: USA Release CD
  link: assets/images/covers/usa_release_cd.jpg
- image_path: assets/images/covers/usa_release_jewelcase_front.jpg
  title: USA Release Jewelcase Front
  link: assets/images/covers/usa_release_jewelcase_front.jpg
- image_path: assets/images/covers/usa_release_jewelcase_back.jpg
  title: USA Release Jewelcase Back
  link: assets/images/covers/usa_release_jewelcase_back.jpg
- image_path: assets/images/covers/usa_release_jewelcase_inlay.jpg
  title: USA Release Jewelcase Inlay
  link: assets/images/covers/usa_release_jewelcase_inlay.jpg
- image_path: assets/images/covers/psx-time-commando-release.jpg
  title: USA PSX Time Commando
  link: assets/images/covers/psx-time-commando-release.jpg
- image_path: assets/images/covers/cd_front_portuguese-spanish.jpeg
  title: Creative Labs Multimedia CD Front PT ES
  link: assets/images/covers/cd_front_portuguese-spanish.jpeg
- image_path: assets/images/covers/cd_expert_br.png
  title: CD Expert BR
  link: assets/images/covers/cd_expert_br.png
- image_path: assets/images/covers/tc-pc-jp-box-front.png
  title: Time Commando PC JP Box Front
  link: assets/images/covers/tc-pc-jp-box-front.png
- image_path: assets/images/covers/tc-pc-jp-box-back.png
  title: Time Commando PC JP Box Back
  link: assets/images/covers/tc-pc-jp-box-back.png
- image_path: assets/images/covers/tc-pc-jp-cd.png
  title: Time Commando PC JP CD
  link: assets/images/covers/tc-pc-jp-cd.png
---

# Covers

<div>
    {% for image in page.images %}
        <a href="{{ site.baseurl }}/{{ image.link }}" style="margin: 6px; display: inline-flex; border-radius: 15px; border: 1px solid #80808042; padding: 5px;">
            <img src="{{ site.baseurl }}/{{ image.image_path }}" alt="{{ image.title}}" style="border-radius: 10px" />
        </a>
    {% endfor %}
</div>

Partial Source: [https://magicball.net/other/galleries/time-commando/cover-art/](https://magicball.net/other/galleries/time-commando/cover-art/)
