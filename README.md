### Algoritmos y Estructuras de Datos III
# Trabajo práctico Nº 3

## Tareas pendientes (para el viernes 17/06):
* Franco: terminar explicación y demostración de correctitud y complejidad del
  ejercicio 3.

* Maxi: tener andando el código del ejercicio 3. Esto quiere decir que compile
  (para ver eso alcanza con un compilador) y que haga lo que tiene que hacer
  (para ver eso hacen falta aunque sea tres o cuatro casos de test bien
  elegidos).

* Franco y Maxi, si queda tiempo: avanzar lo posible con la experimentación
  del 3.

* Manu: tener andando el código del ejercicio 2. Ídem todo lo que le dije a
  Maxi. Me acabo de dar cuenta que, si queda tiempo, sería bueno empezar
  aunque sea a bosquejar el informe.

* Iván: terminar el framework de experimentación y empezar con la
  experimentación del 2 (i.e. generación de casos y estructura de los
  experimentos).

* TODOS: Bajar *en papel* las heurísticas golosas que planteamos hoy. Esto
  incluye:
  1. tener algún tipo de pseudocódigo, y las ideas bien claras sobre cuál es
     el criterio para elegir tanto los nodos como las aristas que se eligen en
     cada paso.
  2. tener una idea (bien) aproximada de la complejidad.
  3. pensar aspectos positivos y negativos, casos en los que funciona muy bien
     y casos en los que es posible que pinche. Todo esto bocetado en papel,
     así el viernes lo primero que hacemos es sentarnos con todas las ideas y
     ver cómo sigue la implementación.

* Además, ir escribiendo todo lo que se les ocurra sobre estas dos cosas:
  * Familias de grafos interesantes para experimentar con las heurísticas, e
    ideas para generarlas y testearlas.
  * Métricas y técnicas para comparar distintas heurísticas en cuanto a
    calidad de los resultados.

## General
* **Fecha de entrega**: viernes 24 de junio, hasta las 18:00 horas.
* **Formato de entrega**:
  * Informe impreso que desarrolle los puntos mencionados en el enunciado.
  * El mismo informe en formato digital acompañado de los códigos fuentes
    desarrollados e instrucciones de compilación, de ser necesarias. Enviar a
    la dirección `algo3.dc@gmail.com` con el asunto `TP 3: Apellido 1, ...,
    Apellido n`, donde *n* es la cantidad de integrantes del grupo y *Apellido
    i* es el apellido del *i*-ésimo integrante.
* **Consideraciones**: La entrada y salida de los programas deberá hacerse por
  medio de la entrada y salida estándar del sistema. No se deben considerar
  los tiempos de lectura/escritura al medir los tiempos de ejecución de los
  programas implementados.

## Resumen de ejercicios
1. Leer paper de Ehrlich y Rarey, explicar qué problema se busca resolver en
   el mismo, encontrar las diferencias entre dicho problema y MCS, explicar
   qué aplicaciones tiene este problema en la química.
2. Diseñar e implementar un algoritmo exacto para MCS.
   1. Explicar detalladamente el algoritmo, elaborar podas y
      estrategias que permitan mejorar los tiempos de resolución.
   2. Calcular el orden de complejidad temporal de peor caso.
   3. Realizar experimentación que permita observar tiempos de ejecución en
      función del tamaño de entrada y de las podas y/o estrategias
      implementadas.
3. Diseñar e implementar un algoritmo exacto para MCS que tenga complejidad
   temporal polinomial para G1 cografo y G2 grafo completo.
   1. Explicar detalladamente el algoritmo implementado.
   2. Calcular el orden de complejidad temporal de peor caso.
   3. Realizar una experimentación que permita observar tiempos de ejecución
      en función del tamaño de entrada.
4. Diseñar e implementar una heurística constructiva golosa para MCS.
   1. Explicar detalladamente el algoritmo implementado.
   2. Calcular el orden de complejidad temporal de peor caso.
   3. Describir instancias para las cuales la heurística no proporciona una
      solución óptima; indicar qué tan mala puede ser respecto de la solución
      óptima.
   4. Realizar experimentación que permita observar performance en
      términos de tiempo de ejecución en función del tamaño de entrada.
5. Diseñar e implementar una heurística de búsqueda local para MCS.
   1. Explicar detalladamente el algoritmo implementado. Plantear al menos dos
      vecindades distintas para la búsqueda.
   2. Calcular el orden de complejidad temporal de peor caso de una iteración
      del algoritmo de búsqueda local (para las vecindades planteadas). Si es
      posible, dar una cota superior para la cantidad de iteraciones.
   3. Realizar experimentación que permita observar performance comparando los
      tiempos de ejecución y la calidad de las soluciones obtenidas, en
      función de las vecindades y elegir, si es posible, la configuración que
      mejores resultados provea para el grupo de instancias utilizado.
6. Diseñar e implementar un algoritmo para MCS que incluya la metaheurística
   Taboo Search.
   1. Explicar detalladamente el algoritmo implementado. Plantear distintos
      criterios de parada y de tamaño de la lista tabú de la heurística.
   2. Realizar experimentación que permita observar tiempos de ejecución y
      calidad de las soluciones obtenidas. Variar los valores de los
      parámetros de la metaheurística (tamaño de la lista taboo, criterios de
      parada, etc.) y las vecindades utilizadas en la búsqueda local. Elegir,
      si es posible, la configuración que mejores resultados provea para el
      grupo de instancias utilizado.
7. Una vez elegidos los mejores valores de configuración para cada heurística
   implementada (si fue posible), realizar una experimentación sobre un
   conjunto nuevo de instancias para observar la performance de los métodos,
   comparando nuevamente calidad de las soluciones obtenidas y tiempos de
   ejecución en función del tamaño de entrada. Para los casos en los que sea
   posible, comparar también los resultados contra los del algoritmo exacto.
   Presentar todos los resultados obtenidos mediante gráficos adecuados (u
   otras opciones que se consideren provechosas) y discutir al respecto de los
   mismos.
8. EXTRA y NO OBLIGATORIO: implementar un código en C++ que use cualquier
   técnica algorítmica o heurística pero que demore no más de 15 segundos en
   terminar. Este ejercicio debe ser resuelto en grupos de a lo sumo dos
   personas. Todos los códigos entregados como parte de este ejercicio
   competirán por un premio.
