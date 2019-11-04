Modulo I - Sesion 04
=======================

Automatizacion de Tareas

### Actividad 4.1. Orden at.

```console
	ps aux
```

### Actividad 4.4. Cuestiones sobre at.

```console
	# Ejercicio a) El trabajo hereda el entorno actual, por lo que se ejecuta en el mismo directorio de trabajo.
	# Ejercicio b) El umask es 0022. Es la heredada del padre.
	# Ejercicio c) Si, hereda las variables de entorno establecidas como cuando fue programado.
```

### Actividad 4.6. Script para Orden at.

```bash
	#!/bin/bash
	find /home -mtime 1 > modificados:`date +%Y-%j-%T`
```

```console
	at -f ./script now+1 day
```

### Actividad 4.11. Ejecucion de Scripts con crontab.

```bash
	#!/bin/bash
	head -n 10 /tmp/listacores > /tmp/temporal
	rm /tmp/listacores
	mv /tmp/temporal /tmp/listacores

	SHELL=/bin/sh
	PATH=/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr:/sbin:/usr/bin
	* * * * * ~/SO/reducelista

	# Los asteriscos del archivo representan la periodicidad. De izquierda a derecha: 
	# minutos, horas , dia del mes, mes y dia de la semana. 
	# Si no se ponen datos en lugar de asteriscos se ejecuta cada minuto, de cada hora, cada dia del mes, de cada mes, cada dia de la semana.
```

```console
	crontab archivo_cron
```

### Actividad 4.13. Variables de Entorno en Archivos crontab.

```bash
	#!/bin/bash
	echo "SHELL=/bin/bash"
	echo "PATH="`pwd`"/:$HOME/SO:"$PATH >> crontab-reducelista
	echo "* * * * * reducelista" >> crontab-reducelista
```

```console
	crontab crontab-reducelista
```
