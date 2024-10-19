---
title: Gifs
layout: home
parent: Gallery
nav_order: 4
permalink: /gallery/gifs
images:
- image_path: assets/images/gifs/flying_suitcase.gif
  title: Flying Suitcase
  link: assets/images/gifs/flying_suitcase.gif
- image_path: assets/images/gifs/game_over_1.gif
  title: Game Over 1
  link: assets/images/gifs/game_over_1.gif
- image_path: assets/images/gifs/game_over_2.gif
  title: Game Over 2
  link: assets/images/gifs/game_over_2.gif
- image_path: assets/images/gifs/game_over_3.gif
  title: Game Over 3
  link: assets/images/gifs/game_over_3.gif
- image_path: assets/images/gifs/game_over_4.gif
  title: Game Over 4
  link: assets/images/gifs/game_over_4.gif
- image_path: assets/images/gifs/stanley_playing_himself.gif
  title: Stanley Playing Himself
  link: assets/images/gifs/stanley_playing_himself.gif
- image_path: assets/images/gifs/tunel_stanley.gif
  title: Stanley in the Tunnel
  link: assets/images/gifs/tunel_stanley.gif
---

# Gifs

<div>
    {% for image in page.images %}
        <a href="{{ site.baseurl }}/{{ image.link }}" style="margin: 6px; display: inline-flex; border-radius: 15px; border: 1px solid #80808042; padding: 5px;">
            <img src="{{ site.baseurl }}/{{ image.image_path }}" alt="{{ image.title}}" style="border-radius: 10px" />
        </a>
    {% endfor %}
</div>

Source: [https://blog.defence-force.org/?tag=Time%20Commando](https://blog.defence-force.org/?tag=Time%20Commando)

