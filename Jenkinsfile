pipeline {
    agent any

    stages {
        stage('Checkout Code') {
            steps {
                checkout scm
            }
        }

        stage('Conan Install') {
            steps {
                sh 'conan install . --output-folder=build --build=missing'
            }
        }

        stage('CMake Configure') {
            steps {
                sh 'cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake'
            }
        }

        stage('Build') {
            steps {
                sh 'cmake --build build --config Release'
            }
        }

        stage('Run Tests') {
            steps {
                sh 'ctest --test-dir build --output-on-failure'
            }
        }

        stage('Static Analysis') {
            steps {
                sh 'cppcheck --enable=all --error-exitcode=0 src include'
            }
        }

        stage('Generate Package') {
            steps {
                sh 'cd build && cpack'
            }
        }

        stage('Publish Artifacts') {
            steps {
                archiveArtifacts artifacts: 'build/*.tar.gz, build/*.deb, build/*.zip', fingerprint: true
            }
        }
    }
}
