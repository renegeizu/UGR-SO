Modulo I - Sesion 02
=======================

Herramientas de Administracion Basicas

### Actividad 2.2. Creacion de Sistemas de Archivos

```console
	mke2fs -L LABEL_ext3 -J size=1 -t ext3 /dev/loop0
	mke2fs -L LABEL_ext4 -J size=1 -t ext4 /dev/loop1
```

### Actividad 2.3. Personalizacion de los Metadatos del SA

```console
	tune2fs -C <mount-count>
	# El parámetro mount-count debe ser mayor que el valor max-mount-coun del parámetro -c.
```

```console
	tune2fs /dev/loop0 –r <numero-bloques> –u <username>
```

### Actividad 2.7. Trabajo con el Gestor de Paquetes YUM

```console
	# El archivo de configuración de YUM se encuentra en /etc/yum/yum.conf

	# Para listar los paquetes instalados y disponibles:
	yum list installed

	# Para borrar un paquete instalado:
	yum remove <paquete a borrar>

	# Para instalar un paquete:
	yum install <paquete a instalar>
```

### Actividad 2.8. Trabajo con el Gestor de Paquetes rpm

```console
	rpm -qli <paquete>
```

```console
	rpm -qc <paquete>
```

```console
	rpm -q --whatrequires <paquete>
```

```console
	rpm -ivh /fenix/depar/lsi/so/paquetes/quota-3.17-13.fc14.i686.rpm
```

```console
	rpm -ivh /fenix/depar/lsi/so/paquetes/sysstat-9.0.6-3.fc13.i686.rpm
	rpm -e --nodeps -v sysstat-9.0.6-3.fc13.i686
```

### Actividad 2.10. Establecer Limites sobre Recursos de un SA

```console
	# Metodo 01
	edquota -u <usuario> -f /etc/loop0

	# Metodo 02
	setquota -u <usuario> 25 30 0 0 /etc/loop0
```
