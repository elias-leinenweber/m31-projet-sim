# M31 - Projet "Simulation" en C

## Sujet 14 : Aloha discrétisé

On rappelle l'énoncé :

> **Aloha discrétisé**
>
> L'idée du projet est de simuler le fonctionnement de n stations se partageant
> un canal de communication unique, et s'emparant du canal lorsqu'elles
> souhaitent l'utiliser, indépendamment l'une de l'autre.
>
> Le temps est discrétisé, découpé en *slots*, et chaque station a une
> probabilité p (valeur commune à toutes les stations) de commencer une émission
> au début d'un slot. Lorsque deux stations émettent dans le même slot, il y a
> collision, et dans ce cas, elles doivent ré-émettre leur message
> ultérieurement. Pour déterminer le moment de la ré-émission, la station
> choisit un slot au hasard uniformément parmi les K slots suivants (K étant un
> paramètre commun à l'ensemble des stations partageant le canal).
>
> Un slot est *utile* lorsqu'il permet de transmettre effectivement un message ;
> il faut donc qu'il y ait une émission, et une seule, durant le slot. Il n'y a
> pas d'abandon de la transmission au bout d'un nombre donné d'échecs.
> Simuler le fonctionnement du système pour une durée de 100 slots, avec p=0.01
> et k=4, et évaluer l'efficacité du système en fonction de n (compris entre 10
> et 100) : on pourra mesurer le nombre de slots utiles, ou le nombre de
> messages en attente d'émission, par exemple.
