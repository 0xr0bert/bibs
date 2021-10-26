FROM fedora:35

RUN dnf upgrade -y && \
	dnf install -y meson clang llvm lld gtest-devel gmock-devel boost-devel

WORKDIR /data
