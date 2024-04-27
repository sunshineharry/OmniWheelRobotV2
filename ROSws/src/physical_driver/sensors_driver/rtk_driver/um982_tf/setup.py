from setuptools import find_packages, setup

package_name = 'um982_tf'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='root',
    maintainer_email='hankunjiang@outlook.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'world_to_map_node = um982_tf.world_to_map_node:main',
            'rtkantenna_to_baselink_node = um982_tf.rtkantenna_to_baselink_node:main',
        ],
    },
)
