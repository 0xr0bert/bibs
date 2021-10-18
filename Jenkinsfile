pipeline {
	agent { docker { image 'ragreener1/bibs-jenkins' } }
	stages {
		stage('log version info') {
			steps {
				sh 'meson --version'
			}
		}
	}
}
