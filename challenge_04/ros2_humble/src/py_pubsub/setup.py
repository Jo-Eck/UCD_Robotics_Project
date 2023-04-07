from setuptools import setup

package_name = 'py_pubsub'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='jon',
    maintainer_email='48563777+Jo-Eck@users.noreply.github.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
                            'number_publisher = py_pubsub.number_publisher:main',
                            'number_counter = py_pubsub.number_counter:main',
                            'listener = py_pubsub.subscriber_member_function:main'
        ],
    },
)
