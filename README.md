# M31 - Projet "Simulation" en C

**Sujet :** n° 14 - Aloha discrétisé

## Génération du compte-rendu

```
$ ./run.sh
```

### Dépendances
- `R`
- `pandoc`
- `pdflatex`

## Prolongements possibles

- Messages durant plus d'un slot : fixe ; ou variable, (cette durée pourrait
  être une v.a. de loi uniforme, même si une loi de Poisson pourrait paraître
  mieux adaptée, mais bon, ça devient compliqué)
- Faire varier p, k et n : essayer de voir quelles sont les variations qui ont
  un effet significatif/intéressant sur la congestion ou non du système
- En fait pour la probabilité d'émissions, ce qui serait déjà plus réaliste, ce
  serait un  modèle markovien où la proba d'émission au prochain slot dépendrait
  du fait d'émettre pendant le slot courant (il y a plus de chance que vous
  soyez en train de parler dans une seconde si vous êtes déjà en train de
  parler !)
- Le nombre de messages en attente d'émission à la fin de la simulation, à un
  moment donné (évolution au cours du temps), ou bien en tout ?
  > on pourra : c'est une piste, pas un impératif, c'est ouvert
  > - dans un premier temps je regarderais l'état à la fin de la simulation
  >   parce que c'est le plus simple, et ça peut déjà m'alerter sur
  >   l'inadéquation des paramètres à la charge
  > - je pourrais aussi stocker le max de ce nombre sur l'ensemble des slots
  > - enfin en observer l'évolution temporelle
- Et y a-t-il possibilité pour une station de vouloir envoyer un nouveau message
  alors qu'il y a déjà un message en attente?
  > [11:35 AM] H.: je dirais que oui, vu que le paramètre p est constant pour
  >                les machines et dans le temps
  >
  > [11:36 AM] H.: mais on peut aussi bloquer la volonté d'émission d'une
  >                machine lorsqu'elle est en attente d'émission
  >
  > [11:37 AM] H.: (Aloha est un protocole radio au départ, et on peut imaginer
  >                qu'on n'émet pas un nouveau message tant qu'on n'a pas eu de
  >                réponse au premier)
