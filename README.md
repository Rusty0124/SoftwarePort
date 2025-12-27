# Lance Shaffer - Portfolio Website

A modern, responsive portfolio website showcasing proficiency in C++, Python, and JavaScript.

## Features

- **Modern Design**: Clean, professional interface with gradient accents and smooth animations
- **Responsive Layout**: Works seamlessly on desktop, tablet, and mobile devices
- **Interactive Elements**: Smooth animations, scroll effects, and modal project demos
- **Project Showcase**: 6 fully functional projects demonstrating skills in C++, Python, and JavaScript
- **Live Demos**: Interactive demos for each project embedded in modal windows
- **Docker Support**: Containerized for easy deployment
- **Contact Form**: Easy way for potential clients/employers to reach out

## Technologies Used

- HTML5
- CSS3 (with CSS Grid and Flexbox)
- Vanilla JavaScript (ES6+)
- Google Fonts (Inter)

## Getting Started

### Option 1: Direct Browser (No Docker)
1. Clone or download this repository
2. Open `index.html` in your web browser
3. No build process required - it's ready to use!

### Option 2: Using Docker (Recommended)
1. Make sure Docker and Docker Compose are installed on your system
2. Build and run the container:
   ```bash
   docker-compose up -d
   ```
3. Open your browser and navigate to `http://localhost:8080`
4. To stop the container:
   ```bash
   docker-compose down
   ```

#### Docker Commands
- **Build the image**: `docker-compose build`
- **Start the container**: `docker-compose up -d`
- **Stop the container**: `docker-compose down`
- **View logs**: `docker-compose logs -f`
- **Rebuild after changes**: `docker-compose up -d --build`

## Customization

### Update Contact Information
Edit the contact section in `index.html`:
- Email address
- LinkedIn profile
- GitHub username

### Add Your Projects
Update the project cards in the projects section with:
- Your actual project names and descriptions
- Links to GitHub repositories
- Links to live demos
- Technologies used

### Modify Colors
Edit the CSS variables in `styles.css`:
```css
:root {
    --primary-color: #6366f1;
    --secondary-color: #8b5cf6;
    --accent: #06b6d4;
    /* ... */
}
```

## Project Structure

```
Portfilo/
├── index.html          # Main HTML file
├── styles.css          # All styling
├── script.js           # JavaScript functionality
├── Dockerfile          # Docker container configuration
├── docker-compose.yml  # Docker Compose configuration
├── nginx.conf          # Nginx web server configuration
├── .dockerignore       # Docker ignore file
├── README.md           # This file
└── projects/           # Project showcase files
    ├── game_engine.h
    ├── game_engine.cpp
    ├── game_engine_demo.html
    ├── ray_tracing_engine.h
    ├── ray_tracing_engine.cpp
    ├── ray_tracing_demo.html
    ├── stock_predictor.py
    ├── stock_predictor_demo.html
    ├── ai_image_classifier.py
    ├── ai_image_classifier_demo.html
    ├── collaborative_platform.html
    ├── ecommerce_dashboard.html
    ├── requirements.txt
    └── README.md
```

## Browser Support

- Chrome (latest)
- Firefox (latest)
- Safari (latest)
- Edge (latest)

## Features Breakdown

### Sections

1. **Hero Section**: Eye-catching introduction with call-to-action buttons
2. **About Section**: Personal introduction and statistics
3. **Skills Section**: Technical skills with visual progress bars
4. **Projects Section**: Showcase of projects in C++, Python, and JavaScript
5. **Contact Section**: Contact form and social links

### Interactive Features

- Smooth scrolling navigation
- Mobile-responsive hamburger menu
- Animated skill bars on scroll
- Project card animations
- Active navigation highlighting
- Contact form validation

## Deployment

### Docker Deployment
The portfolio is containerized and ready for deployment on any Docker-compatible platform:
- **Docker Hub**: Push the image and deploy anywhere
- **AWS ECS/Fargate**: Container orchestration
- **Google Cloud Run**: Serverless container platform
- **Azure Container Instances**: Simple container hosting
- **DigitalOcean App Platform**: Easy container deployment

### Other Deployment Options
- **GitHub Pages**: Free hosting for static sites
- **Netlify**: Drag and drop deployment
- **Vercel**: Fast deployment with Git integration
- **Any static hosting service**

### Docker Production Deployment
For production, you can:
1. Build the image: `docker build -t lance-shaffer-portfolio .`
2. Tag for registry: `docker tag lance-shaffer-portfolio your-registry/lance-shaffer-portfolio:latest`
3. Push to registry: `docker push your-registry/lance-shaffer-portfolio:latest`
4. Deploy to your container platform

## License

This project is open source and available for personal use.

## Contact

Lance Shaffer
- Email: lance.shaffer@email.com
- LinkedIn: /in/lanceshaffer
- GitHub: [@Rusty0124](https://github.com/Rusty0124)

