Modulo I - Sesion 03
=======================

Monitorizacion del Sistema

### Actividad 3.1. Consulta de Estadisticas del Sistema.

```console
	# Primera Orden
	uptime

	# Segunda Orden
	w
```

### Actividad 3.2. Prioridad de los Procesos.

```bash
	#!/bin/bash
	parametro=$1
	if [ -z ${parametro} ]; then
		echo "Falta especificar el parametro"
	else
		x = 0
		while [ $x != $parametro ]; do
			let x+=1
		done
		echo "El valor obtenido es" $x
	fi
```

```console
	./prueba_procesos 1000000000 &
	./prueba_procesos 2000000000 &

	# Compruebo los Procesos
	top

	# Consigo los PID del proceso 1 y del 2, y Cambio Prioridad
	renice -10 PID1
	renice 10 PID2

	# Compruebo los Procesos
	top
```

```console
	time ./prueba_procesos 1000
	time ./prueba_procesos 10000
```


### Actividad 3.4. Estadisticas de Recursos del Sistema.

```console
	mpstat
	# Podemos ver el porcentaje de CPU usado para atender interrupciones hardware en la columna %irq.
	# Podemos ver el porcentaje de CPU usado para atender interrupciones software en la columna %soft.
	
	top
	# El espacio libre del Swap lo vemos en la linea ‘KiB Swap’.
```

### Actividad 3.6. Utilizacion de vmstat.

```console
	vmstat 2 20 >> datos.dat
	# La orden indica que realice 20 iteraciones de la orden vmstat, una iteración cada 2 segundos.
```

### Actividad 3.8. Listados de Metadatos de Archivos: ls.

```console
	ls -ltu
	ls -ltc
```

### Actividad 3.9. Metadatos del Sistema de Archivos: df y du.

```console
	# Ejercicio 1)
	du /
	# En formato “human readable format”:
	du -h /

	# Ejercicio 2)
	df -i /
	# Se podrían crear tantos como i-nodos libres

	# Ejercicio 3)
	du -h /etc
	# Dentro de este directorio, el sistema, guarda los archivos de configuración del sistema y de las aplicaciones instaladas.
	du –h /var
	# Dentro de este directorio se encuentran ficheros variables como ficheros temporales.
	du -h /bin
	# Dentro de este directorio se guardan comandos y programas binarios esenciales.
	du –h /usr
	# En este directorio se encuentran los programas instalados.
	du –h /lib
	# Dentro de este directorio se guardan las librerías del sistema.
```

### Actividad 3.10. Creacion de Enlaces con la Orden ln.

```console
	ln -s archivo.txt ./softLink
	ln archivo.txt hardlink
	ln target_hardLink2.txt hardlink2
	mkdir D1/
	ls -lai
	cd D1
	ls -lai

	# Diferencias entre softlink y hardlink:
	# Los softlink se pueden hacer con ficheros y directorios mientras que los hardlink solo entre ficheros.
	# Los softlink se pueden hacer entre distintos sistemas de ficheros, los hardlink no.
	# Los hardlink comparten el número de inodo, los softlink no.
	# En los softlink si se borra el fichero o directorio original, la información se pierde, en los hardlink no.
	# Los hardlink son copias exactas del fichero mientras que los softlink son meros punteros o “accesos directos”.
	
	# Los enlaces softlink no cuentan pues son simples punteros mientras que los hardlink son copias del fichero.
```

### Actividad 3.12. Creacion de Archivos Especiales.

```console
	mknod dispBloques b 100 10
	mknod dispCaracteres c 50 5
	ls -li
```
