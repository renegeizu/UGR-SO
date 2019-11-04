Modulo I - Sesion 01
=======================

Herramientas de Administracion Basicas

### Actividad 1.1. Repaso de Scripts de Bash

```console
	#!/bin/bash
	cp /fenix/depar/lsi/UML/*.gz /tmp
	cd /tmp
	gunzip *.gz
	./kernel32-3.0.4 ubda=./Fedora14-x86-root_fs mem=1024m
```

### Actividad 1.3. Creacion de Usuarios

```console
	sudo groupadd fairytail
	sudo useradd -d /home/natsu –m -g fairytail natsu
	sudo passwd natsu
	sudo useradd -d /home/gray –m -s /bin/bash gray
	sudo passwd gray
```

```console
	sudo userdel natsu
	# Deja su carpeta en /home/natsu
```

```console
	su gray
	ls -a /home/gray
	# Lista de Archivos: .bash_logout .bashrc examples.desktop .profile
```

### Actividad 1.6. Creacion de Grupos

```console
	sudo groupadd icemaker
	sudo gpasswd -a gray icemaker
```

```console
	# uid=0(root) gid=0(root) grupos=0(root)
```

### Actividad 1.8. Organizacion del SA

```console
	# /var/tmp
```

### Actividad 1.10 Informacion de los SAs

```console
	# <file system> Partición o dispositivo de almacenamiento a montar
	# <mount point> Indica a la orden mount el punto de montaje donde la partición (<file system>) será montada
	# <type> Indica el tipo de sistema de archivos de la partición o dispositivo
	# <options> Opciones de montaje (Usado por la orden mount)
	# <dump> Indica si hay que hacer respaldo (1) o se ignora (0) el sistema de archivos (Usado por el programa dump)
	# <pass> Orden de comprobacion del sistema de archivos (1) como prioridad mas alta, le sigue (2) y (0) para no comprobar (Usado por fsck)
```
