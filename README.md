# Supemon Project

## Informations importantes

J’ai utilisé la fonction `strcpy`, qui n’a pas été vue en cours.  
Elle sert simplement à copier des chaînes de caractères (par exemple pour stocker des noms ou des types).

Je l’ai utilisée parce que c’était la solution la plus simple pour gérer les chaînes en C.


# Supemon Project

Supemon est un jeu de type RPG inspiré de Pokémon, développé en C. Le joueur peut capturer des Supemons, combattre des ennemis sauvages, visiter un centre pour soigner ses Supemons, gérer son inventaire et acheter des objets dans le shop.

---

## Fonctionnalités

- **Choix du joueur** : possibilité de choisir son Supemon de départ.
- **Combat** : affrontement contre des Supemons sauvages avec des attaques offensives et des objets.
- **Système de fuite** : possibilité de tenter de fuir un combat selon la vitesse du Supemon.
- **Inventaire** : gestion des potions, super potions et super bonbons.
- **Shop** : acheter et vendre des objets avec les Supecoins.
- **Centre Supemon** : soigner tous les Supemons.
- **Sauvegarde et chargement** : sauvegarde automatique du joueur dans un fichier `save.dat`.

---

## Compilation

Pour compiler le projet sous Windows avec GCC :

```bash
gcc main.c menu.c combat.c center.c shop.c choix_valide.c save.c inventaire.c -o main.exe
