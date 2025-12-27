# GitHub Pages Setup Guide

Your portfolio is ready to be hosted on GitHub Pages! Here's how to set it up:

## Quick Setup

1. **Push your code to GitHub**
   ```bash
   git init
   git add .
   git commit -m "Initial commit"
   git remote add origin https://github.com/Rusty0124/Portfilo.git
   git push -u origin main
   ```

2. **Enable GitHub Pages**
   - Go to your repository on GitHub
   - Click on **Settings**
   - Scroll down to **Pages** in the left sidebar
   - Under **Source**, select **Deploy from a branch**
   - Choose **main** branch and **/ (root)** folder
   - Click **Save**

3. **Your site will be live at:**
   - `https://rusty0124.github.io/Portfilo/` (if repo is named "Portfilo")
   - OR `https://rusty0124.github.io/` (if repo is named "rusty0124.github.io")

## Important Notes

- The `.nojekyll` file ensures GitHub Pages serves all files correctly
- All paths are already relative, so they'll work on GitHub Pages
- Docker files (`Dockerfile`, `docker-compose.yml`, `nginx.conf`) won't affect GitHub Pages - they're just for local development
- Your site will be available within a few minutes after enabling Pages

## Custom Domain (Optional)

If you want to use a custom domain:
1. Add a `CNAME` file in the root with your domain name
2. Configure DNS records as per GitHub Pages documentation

## Testing Locally

You can test the site locally before pushing:
- Just open `index.html` in a browser
- Or use the Docker setup: `docker-compose up`

