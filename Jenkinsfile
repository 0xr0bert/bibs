pipeline {
	agent { docker { image 'ragreener1/bibs-jenkins' } }
	stages {
		stage('log version info') {
			steps {
				sh 'meson --version'
			}
		}
		stage('build') {
			steps {
				sh 'CC=clang CC_LD=lld CXX=clang++ CXX_LD=lld meson setup build'
				sh 'cd build'
				sh 'meson compile'
			}
		}
	}
}
