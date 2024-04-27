from setuptools import find_packages, setup

package_name = 'kinematics_model'

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
    maintainer='orangepi',
    maintainer_email='1544453976@qq.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "kinematics_model2_node = kinematics_model.kinematics_model2:main",
            "kinematics_model1_node = kinematics_model.kinematics_model1:main",
        ],
    },
)
