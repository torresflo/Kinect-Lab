![GitHub license](https://img.shields.io/github/license/torresflo/Kinect-Lab.svg)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](http://makeapullrequest.com)
![GitHub contributors](https://img.shields.io/github/contributors/torresflo/Kinect-Lab.svg)
![GitHub issues](https://img.shields.io/github/issues/torresflo/Kinect-Lab.svg)

<p align="center">
  <h1 align="center">Kinect Lab</h3>

  <p align="center">
    A C++ library to access and manipulate Kinect data easily.
    <br />
    <a href="https://github.com/torresflo/Kinect-Lab/issues">Report a bug or request a feature</a>
  </p>
</p>

## Table of Contents

* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
  * [Example](#example)
* [Contributing](#contributing)
* [License](#license)

## Getting Started

### Prerequisites

- The project is supposed to be compiled on <a href="https://visualstudio.microsoft.com/fr/downloads/">Visual Studio</a>.
- The <a href="https://www.microsoft.com/en-us/download/details.aspx?id=40278">Kinect for Windows SDK 1.8</a> should be installed on your computer. The project's configuration files will use the environment variable `$(KINECTSDK10_DIR)` to search for the includes and the libs. This variable should be set automatically when installing the SDK.
- The file `main.cpp` is using OpenGL and <a href="http://freeglut.sourceforge.net/">freeglut</a>. Create a folder `libs` at the root of the project that contains a folder `freeglut`. This directory should contain the folders `bin`, `lib` and `include` of the freeglut library.

### Installation

Follow the instructions above, then clone the repo (`git clone https:://github.com/torresflo/Kinect-Lab.git`) and build the project.

## Usage

You can have a look at `main.cpp` or see the example below.

### Example

```cpp
#include <KinectCore\Kinect\Sensor.hpp>

Kinect::Sensor sensor;
Kinect::Error lastError = sensor.init(); //Init the sensor, you can precise an index if you have multiple devices connected

if (lastError == Kinect::Error::NoError)
{
    lastError = sensor.update();
    
    //Let's retrieve information from the sensor
    const Container::Array2D<Math::Scalar8UC3>& colorImage = sensor.getColorImage(); //2D Array of (R, G, B) values
    const Container::Array2D<Math::Scalar32FC3>& depthImage = sensor.getDepthImage(); //2D Array of depth values in millimeters
    const Container::Array2D<unsigned short>& playersIndex = sensor.getPlayersIndex(); //2D Array of players index (from 1 to 6).
    
    std::vector<Kinect::Skeleton> skeletons = sensor.getSkeletons(); //Vector of available skeletons
    for(const Kinect::Skeleton& skeleton : skeletons)
    {
        const Math::Vector3f& headPosition = skeleton.getPosition(Kinect::SkeletonPosition::Head);
        const Math::Vector3f& handLeftPosition = skeleton.getPosition(Kinect::SkeletonPosition::HandLeft);
        //...
    }
    //...
}
```

## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<!-- LICENSE -->
## License

Distributed under the GNU General Public License v3.0. See `LICENSE` for more information.
