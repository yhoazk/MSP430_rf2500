# Basic commands for podman

Podman replaces most of the functionality of the Docker CI, it has the
advantage that it does not run a fat daemon like docker does. This means that
it can be integrated into system using `systemd`.

Given that `podman` has the same syntax as `docker` the command can be replaced
with the next command in the `.bashrc`.

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