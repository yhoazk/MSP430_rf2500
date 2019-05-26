# Example Dockerfile to use with podman
# It will create a alpine image with git and vim

# Get the base image
FROM alpine:3.4
# Even when this is a bad practice add the needed pkgs
# This is a bad practice as every RUN command will create
# a step in the build and this makes the build slower

# RUN apk update
# RUN apk add vim
# RUN apk add curl
# RUN apk add git

# The alternative is to run all the steps in a single run
# This will result in only 1 image instead of the 3 used before
# RUN apk update && \
#     apk add vim && \
#     apk add curl && \
#     apk add git

## Even better, run all in a single call

RUN apk update && \
    apk add vim  \
            curl \
            git

RUN mkdir /prj
VOLUME [ "/prj" ]
