#!/usr/bin/bash
# Mount also the device?
podman run -v $(pwd):/prj_src:Z --device localhost/msp_gcc:latest make /prj_src