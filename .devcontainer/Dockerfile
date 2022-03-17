# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.224.2/containers/debian/.devcontainer/base.Dockerfile

# [Choice] Debian version (use bullseye on local arm64/Apple Silicon): bullseye, buster
ARG VARIANT="buster"
FROM mcr.microsoft.com/vscode/devcontainers/base:0-${VARIANT}

# ** [Optional] Uncomment this section to install additional packages. **
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends <your-package-list-here>

RUN sed -i 's|security.debian.org/debian-security|mirrors.ustc.edu.cn/debian-security|g' /etc/apt/sources.list; \
    sed -i 's|deb.debian.org/debian|mirrors.ustc.edu.cn/debian|g' /etc/apt/sources.list; \
    git config --global core.autocrlf true

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive; \
    apt-get -y install --no-install-recommends g++ gdb cmake make