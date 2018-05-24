---
layout: default
---

Text can be **bold**, _italic_, or ~~strikethrough~~.

[Link to another page](./another-page.html).

There should be whitespace between paragraphs.

There should be whitespace between paragraphs. We recommend including a README, or a file with information about your project.

# Header 1

This is a normal paragraph following a header. GitHub is a code hosting platform for version control and collaboration. It lets you and others work together on projects from anywhere.

## Header 2

> This is a blockquote following a header.
>
> When something is important enough, you do it even if the odds are not in your favor.

### Header 3

```js
// Javascript code with syntax highlighting.
var fun = function lang(l) {
  dateformat.i18n = require('./lang/' + l)
  return true;
}
```

```ruby
# Ruby code with syntax highlighting
GitHubPages::Dependencies.gems.each do |gem, version|
  s.add_dependency(gem, "= #{version}")
end
```

#### Header 4

*   This is an unordered list following a header.
*   This is an unordered list following a header.
*   This is an unordered list following a header.

##### Header 5

1.  This is an ordered list following a header.
2.  This is an ordered list following a header.
3.  This is an ordered list following a header.

###### Header 6

| head1        | head two          | three |
|:-------------|:------------------|:------|
| ok           | good swedish fish | nice  |
| out of stock | good and plenty   | nice  |
| ok           | good `oreos`      | hmm   |
| ok           | good `zoute` drop | yumm  |

### There's a horizontal rule below this.

* * *

### Here is an unordered list:

*   Item foo
*   Item bar
*   Item baz
*   Item zip

### And an ordered list:

1.  Item one
1.  Item two
1.  Item three
1.  Item four

### And a nested list:

- level 1 item
  - level 2 item
  - level 2 item
    - level 3 item
    - level 3 item
- level 1 item
  - level 2 item
  - level 2 item
  - level 2 item
- level 1 item
  - level 2 item
  - level 2 item
- level 1 item

### Small image

![Octocat](https://assets-cdn.github.com/images/icons/emoji/octocat.png)

### Large image

![Branching](https://guides.github.com/activities/hello-world/branching.png)


### Definition lists can be used with HTML syntax.

<dl>
<dt>Name</dt>
<dd>Godzilla</dd>
<dt>Born</dt>
<dd>1952</dd>
<dt>Birthplace</dt>
<dd>Japan</dd>
<dt>Color</dt>
<dd>Green</dd>
</dl>

```
Long, single-line code blocks should not wrap. They should horizontally scroll if they are too long. This line should be long enough to demonstrate this.
```

```
The final element.
```

# Projet de Science de L'ingénieur 1ère D

## Projet : L'horloge numérique réglable par 3 boutons poussoirs

Ce projet consiste, avec une carte arduino et des composants comme un afficheur constitué de 4 digits Grove et de son kit de démarrage, à afficher une horloge numérique, que l'utilisateur peut régler grâce à trois boutons. 

### Cahier des charges :
* La conception de votre système doit être réalisé sous forme d'une __machine à
états finis__ cadencé à 10 Hz.
* Votre système doit utilisée l'__horloge temps réel__ intégrée dans la carte 
Arduino
* L'utilisateur doit être en mesure de régler l'heure et les minutes :
    - Il appuie d'abord sur un bouton __réglage__:
        * Cela fait clignoter les 2 digits de gauche de l'afficheur (avec la valeur __00:00__)
        toutes les 0.5 secondes.
    - Il appuie ensuite soit sur un bouton __gauche__ ou un bouton __droite__
    pour incrémenter/decrémenter la valeur affichée des 2 digits de gauche
    (réglage de l'heure)
    - Une fois la valeur choisie, il réappuie sur le bouton __réglage__:
        * Cela arrête le clignotement et fixe la dernière valeur affichée
        sur les 2 digits de gauche de l'afficheur.
        * Cela fait maintenant clignoter les 2 digits de droite de l'afficheur
    - Il appuie ensuite soit sur un bouton __gauche__ ou un bouton __droite__
    pour incrémenter/decrémenter la valeur affichée des 2 digits de droite
    (réglage des minutes)
    - Une fois la valeur choisie, il réappuie sur le bouton __réglage__:
        * Cela arrête le clignotement des 2 digits de droite
        * Les 2 digits de gauche affiche maintenant __l'heure lue__
        * Les 2 digits de droite affiche maintenant __les minutes lues__
        * Le symbole __:__ doit clignoter toutes les secondes

## Déroulement du projet

Ce type de projet devant normalement se faire à 4, étant 2 nous avons donc travailler ensemble sur chaque partie de ce projet (théorique, analyse de code, pratique, communiquer ...) au lycée comme chez nous.

## Partie pratique et démonstration

--------------------------------------------------------------
                mettre image diagramme états/transitions
-----------------------------------------------------------------
--------------------------------------------------------------
_______________________________________________________________


* A l'état initial, l'horloge affiche l'heure normalement.

- lorsque l'on appuie sur le bouton réglage, nous passons à l'états second dans lequel l'horloge est en mode réglage de l'heure, ici l'horloge affiche 00:00 en clignotant.
  - si l'on appuie sur le bouton d'incrémentation, l'heure va s'incrémenter, ainsi à chaque fois que nous appuirons sur le bouton d'incrémentation, nous incrémenterons l'heure.
  - si l'on appuie sur le bouton de décrémentation, l'heure va se décrémenter, et à chaque fois que nous appuirons sur ce bouton, l'heure se décrémentera.
  - si l'on appuie à nouveau sur le bouton réglage, nous passerons au troisième états, dans lequel l'horloge est en mode réglage des minutes.
    - si l'on appuie sur le bouton d'incrémentation, les minutes vont s'incrémenter.
    - si l'on appuie sur le bouton de décrémentation, les minutes vont se décrémenter.
    - si l'on appuie encore une fois sur le bouton de réglage, nous passons au quatrième états, où les données de l'heure et des minutes sont enregistrées et afficher sur le cadran, et ainsi nous repassons directement à l'état initial.

