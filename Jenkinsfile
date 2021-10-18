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
		stage('test') {
			steps {
				dir('build/test') {
					sh './bibs-test --gtest_output=xml:output.xml'
					sh 'awk '{ if ($1 == "<testcase" && match($0, "notrun")) print substr($0,0,length($0)-2) "><skipped/></testcase>"; else print $0;}' output.xml > output-skipped.xml'
					sh 'rm output.xml'
				}
			}
		}
	}
	post {
		always {
			junit 'build/test/output-skipped.xml'
		}
	}
}
