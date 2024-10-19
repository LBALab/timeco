---
title: English
layout: home
parent: Scans
nav_order: 1
permalink: /gallery/scans/english
images_english:
- image_path: assets/images/scans/Computer_Gaming_World_1996-12_1.jpg
  title: Computer Gaming World 1996-12 Page 1
  link: assets/images/scans/Computer_Gaming_World_1996-12_1.jpg
- image_path: assets/images/scans/Computer_Gaming_World_1996-12_2.jpg
  title: Computer Gaming World 1996-12 Page 2
  link: assets/images/scans/Computer_Gaming_World_1996-12_2.jpg
- image_path: assets/images/scans/Computer_Gaming_World_ad_1996-08_1.jpg
  title: Computer Gaming World Ad 1996-08 Page 1
  link: assets/images/scans/Computer_Gaming_World_ad_1996-08_1.jpg
- image_path: assets/images/scans/Computer_Gaming_World_ad_1996-08_2.jpg
  title: Computer Gaming World Ad 1996-08 Page 2
  link: assets/images/scans/Computer_Gaming_World_ad_1996-08_2.jpg
- image_path: assets/images/scans/Computer_Gaming_World_ad_1996-10.jpg
  title: Computer Gaming World Ad 1996-10
  link: assets/images/scans/Computer_Gaming_World_ad_1996-10.jpg
- image_path: assets/images/scans/edge_interview_1996-04_1.jpg
  title: Edge Interview 1996-04 Page 1
  link: assets/images/scans/edge_interview_1996-04_1.jpg
- image_path: assets/images/scans/edge_interview_1996-04_2.jpg
  title: Edge Interview 1996-04 Page 2
  link: assets/images/scans/edge_interview_1996-04_2.jpg
- image_path: assets/images/scans/edge_interview_1996-04_3.jpg
  title: Edge Interview 1996-04 Page 3
  link: assets/images/scans/edge_interview_1996-04_3.jpg
- image_path: assets/images/scans/edge_interview_1996-04_4.jpg
  title: Edge Interview 1996-04 Page 4
  link: assets/images/scans/edge_interview_1996-04_4.jpg
- image_path: assets/images/scans/edge_interview_1996-04_5.jpg
  title: Edge Interview 1996-04 Page 5
  link: assets/images/scans/edge_interview_1996-04_5.jpg
- image_path: assets/images/scans/Gamefan_1996-10.jpg
  title: Gamefan 1996-10
  link: assets/images/scans/Gamefan_1996-10.jpg
- image_path: assets/images/scans/GamePro_1996-07.jpg
  title: GamePro 1996-07
  link: assets/images/scans/GamePro_1996-07.jpg
- image_path: assets/images/scans/Ultra_Game_Players_1996-12.jpg
  title: Ultra Game Players 1996-12
  link: assets/images/scans/Ultra_Game_Players_1996-12.jpg
---

# English Magazines

<div>
    {% for image in page.images_english %}
        <a href="{{ site.baseurl }}/{{ image.link }}" style="margin: 6px; display: inline-flex; border-radius: 15px; border: 1px solid #80808042; padding: 5px;">
            <img src="{{ site.baseurl }}/{{ image.image_path }}" alt="{{ image.title}}" style="border-radius: 10px" />
        </a>
    {% endfor %}
</div>

Source: [https://magicball.net/other/galleries/time-commando/scans/](https://magicball.net/other/galleries/time-commando/scans/)
