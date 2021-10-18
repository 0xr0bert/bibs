pipeline {
	agent { docker { image 'ragreener1/bibs-jenkins' } }
	stages {
		stage('build') {
			steps {
				sh 'CC=clang CC_LD=lld CXX=clang++ CXX_LD=lld meson setup build'
				dir('build') {
					sh 'meson compile'
				}
			}
		}
	}
}
