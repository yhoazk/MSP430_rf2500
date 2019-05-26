# Basic commands for podman

Podman replaces most of the functionality of the Docker CI, it has the
advantage that it _does not run a fat daemon_ like docker does. This means that
it can be integrated into system using `systemd`, plus podman enables the
creation of *rootless containers*, which means that no root access is needed
to deploy containers.

Given that `podman` has the same syntax as `docker` the command can be replaced
with the next command in the `.bashrc`.

The term pod comes from Kubernetes which describes it as
> An object that has one or more conteinerized process sharing multiple 

## `Dockerfile` 

Dockerfile reserved words:

- `CMD`
- `FROM`
- `COPY`
- `RUN`
- `ENV`
- `EXPOSE`



```sh
alias docker=podman
```

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


- - - 

NOTE: Alpine does not use `glibc` instead uses `musl` then programs compiled
in "normal" linux distro will not be able to run here. Either recompile inside
alpine or do not use alpine.