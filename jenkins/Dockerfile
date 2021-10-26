FROM debian:bullseye

RUN apt-get update -y && \
	apt-get upgrade -y && \
	apt-get install -qy openssh-server && \
	sed -i 's|session    required     pam_loginuid.so|session    optional     pam_loginuid.so|g' /etc/pam.d/sshd && \
	mkdir -p /var/run/sshd && \
	apt-get install -qy default-jre && \
	apt-get install -qy default-jdk && \
	apt-get install -qy maven && \
	apt-get install -qy clang && \
	apt-get install -qy lld && \
	apt-get install -qy cmake && \
	apt-get install -qy make && \
	apt-get install -qy git && \
	apt-get install -qy libboost-dev && \
	apt-get install -qy meson && \
	apt-get install -qy googletest &&\
	apt-get install -qy google-mock && \
	adduser jenkins && \
	echo "jenkins:jenkins" | chpasswd && \
	mkdir /home/jenkins/.m2 && \
	ssh-keygen -A

RUN chown -R jenkins:jenkins /home/jenkins/.m2/

EXPOSE 22

CMD ["/usr/sbin/sshd", "-D"]
