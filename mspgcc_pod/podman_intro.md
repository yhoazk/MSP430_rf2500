# Basic commands for podman

Podman replaces most of the functionality of the Docker CI, it has the
advantage that it _does not run a fat daemon_ like docker does. This means that
it can be integrated into system using `systemd`, plus podman enables the
creation of *rootless containers*, which means that no root access is needed
to deploy containers.

Given that `podman` has the same syntax as `docker` the command can be replaced
with the next command in the `.bashrc`.

```sh
alias docker=podman
```

The term pod comes from Kubernetes which describes it as
> An object that has one or more conteinerized process sharing multiple 

## `Dockerfile` 

The `Dockerfile` contains the instructions to build a image, 

Dockerfile reserved words:

- `CMD`
- `FROM`
- `COPY`
- `RUN`
- `ENV`
- `EXPOSE`

#### Show all the locally available containrs

```sh
podman ps -a
```

#### See what is a container doing with `top`

```sh
podman top <container_id>
```

#### View container logs

```sh
podman logs --latest
```

#### Checkpoint the container

```sh
# get the container from fedora
podman pull registry.fedoraproject.org/fedora:30
# run the container with an interactive session
podman run -it registry.fedoraproject.org/fedora:30
# Map the location of the binary into the container
```

## Example `Dockerfile`

Run the local `Dockerfile`

```sh
$ podman build -t podtest/alpine-pork:1.0 .
```

* `docker build`: Build the image from the `Dockerfile`
* `-t podtest/alpine-pork:1.0`: Add the tag name and version
* `.`: The dot at the end of the line is the location of the `Dockerfile`

The output should be sth like:

```sh
$ podman images
REPOSITORY                          TAG      IMAGE ID       CREATED              SIZE
localhost/podtest/apline-pork       1.0      0b1eb296e604   About a minute ago   35.7 MB
registry.fedoraproject.org/fedora   30       edc5d31c9835   4 weeks ago          312 MB
```

The image is built, in order to execute the image interactively:

```sh
podman run --rm -it localhost/podtest/alpine-pork:1.0 /bin/sh
```

When this commadn is executed podman prints to console the several steps
being invoked and indicated with `STEP 1,2,3,4..N :` and after the step is
finished it prints a hash `-->` for the image in that step and stores the
image for reuse. These images can be seen in the registry:

```sh
$ podman images -a
REPOSITORY                          TAG      IMAGE ID       CREATED         SIZE
localhost/podtest/apline-pork       1.0      0b1eb296e604   9 minutes ago   35.7 MB
<none>                              <none>   0fd4f476b828   9 minutes ago   33.8 MB
<none>                              <none>   f7ebb72edb59   9 minutes ago   5.84 MB
```

This images will be used when new docker images are created using the same start point.
In this case the last image will be still there after the new one takes the name and
the old image is now dangling, to remove the dangling images use the next command:

```sh
podman rmi $(docker images -q --filter "dangling=true")
```

## `Dockerfile` best practices

The order in which the `Dockerfile` is relevant because is executed
sequentially, then new images will be created if a intermediate step is
modified. Then follow the next steps to reduce the amount of intermediate
images:

1. Install tools that are needed to build the application
2. Install deps, libs and pkgs
3. Build the application

### Use a `.dockerignore` 


### Add volumes

A volume instructs podman to use the host file system and not the one of the
container, this way the files stored in the volume persist even after the pod
has been removed. 

In the `Dockerfile` create the folder where the volume will be mounted, then
informa podman that the directory will be used as a `VOLUME`, for our example
use:

```sh
podman run --rm -v $PWD:/project:Z -it localhost/podtest/alpine-pork:1.0 /bin/sh
#/ ls /project
Dockerfile podman_intro.md
```
Install a binary inside the container and then checkpoint the container so it
can be used in future compilations w/o rebuild


### Common commands

#### `pull`
#### `push`
#### `build`
#### `run`
#### `commit`

Use a running image as checkpoint, example:

```
$ podman ps 
CONTAINER ID  IMAGE                           COMMAND    CREATED             STATUS                 PORTS  NAMES
b685386f8ba2  localhost/gcc_installed:latest  /bin/bash  About a minute ago  Up About a minute ago         charming_napier
$ podman commit b685386f8ba2 <new_name>
```

Now a new image will be created with all the changes included and named `<new_name>`


#### `tag`
#### `rm`
#### `rmi`

### Empty mounted Volume

When a volume is inside the container, SELinux blocks the read operations, in
one option is to disable SELinux, with `sudo setenforce [ Enforcing | Permisive | 1 | 0 ]`
which turns off the protection, but that is NOT recomended. Instead change the
permision of the volume with the flag `:z` in the volume option.

```sh
podman run -v /home/user:/host_home:z fedora /bin/bash
```

The `:z` will execute: 

```sh
chcon -Rt svirt_sandbox_file_t /home/user
```
That tells selinux that that folder will be shared between containers, all
containers will have R/W access to this folder.

The option `Z` (uppercase), enables protection between containers, this bind
is only R/W for the specific container.

## Squash Images



## Save Image

Once we have a final image, it can be saved in a file.

This saves the image `msp_gcc` to the archive `msp_gcc`

```
podman save localhost/msp_gcc:latest -o msp_gcc
```

Now we can clean all:
* This remove all the images *
```sh
podman rmi -f -a 
```

This can also work:



```
podman images --quit | xargs -L1 -p podman rmi -f
```

## Restore image from file

```
$ podman load --input ./msp_gcc
Getting image source signatures
Copying blob ebded842e85f done
Copying blob 90778c4e8a83 done
Copying blob 592fc88f2320 done
Copying blob 80ad3fbe7a6d done
Copying blob 386083e14cf1 done
Copying blob 4689d24eb2f1 done
Copying config 910ef5f80a done
Writing manifest to image destination
Storing signatures
Loaded image(s): localhost/msp_gcc:late
```

Now the image should be available:

```
$ podman images
REPOSITORY          TAG      IMAGE ID       CREATED          SIZE
localhost/msp_gcc   latest   910ef5f80a85   17 minutes ago   929 MB
```





- - - 

NOTE: Alpine does not use `glibc` instead uses `musl` then programs compiled
in "normal" linux distro will not be able to run here. Either recompile inside
alpine or do not use alpine.