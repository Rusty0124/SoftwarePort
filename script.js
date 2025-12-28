// Mobile Navigation Toggle
const hamburger = document.querySelector('.hamburger');
const navMenu = document.querySelector('.nav-menu');

if (hamburger && navMenu) {
    hamburger.addEventListener('click', () => {
        navMenu.classList.toggle('active');
    });
}

// Close mobile menu when clicking on a link
document.querySelectorAll('.nav-menu a').forEach(link => {
    link.addEventListener('click', () => {
        navMenu.classList.remove('active');
    });
});

// Smooth scroll for navigation links
document.querySelectorAll('a[href^="#"]').forEach(anchor => {
    anchor.addEventListener('click', function (e) {
        e.preventDefault();
        const href = this.getAttribute('href');
        if (href && href !== '#' && href.length > 1) {
            const target = document.querySelector(href);
            if (target) {
                target.scrollIntoView({
                    behavior: 'smooth',
                    block: 'start'
                });
            }
        }
    });
});

// Animate sections on scroll
const sectionObserver = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            entry.target.classList.add('visible');
        }
    });
}, {
    threshold: 0.1,
    rootMargin: '0px 0px -100px 0px'
});

// Observe all sections
document.querySelectorAll('section').forEach(section => {
    sectionObserver.observe(section);
});

// Make hero section visible immediately
const heroSection = document.querySelector('#home');
if (heroSection) {
    heroSection.classList.add('visible');
}

// Animate skill bars on scroll
const skillObserverOptions = {
    threshold: 0.5,
    rootMargin: '0px'
};

const skillObserver = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            const skillBar = entry.target.querySelector('.skill-bar');
            if (skillBar) {
                const width = skillBar.style.width;
                skillBar.style.width = '0';
                setTimeout(() => {
                    skillBar.style.width = width;
                }, 100);
            }
        }
    });
}, skillObserverOptions);

document.querySelectorAll('.skill-card').forEach(card => {
    skillObserver.observe(card);
});

// Navbar scroll effects
let lastScroll = 0;
window.addEventListener('scroll', () => {
    const navbar = document.querySelector('.navbar');
    const scrollProgress = document.getElementById('scrollProgress');
    
    if (navbar) {
        if (window.scrollY > 50) {
            navbar.classList.add('scrolled');
            navbar.style.background = 'rgba(15, 23, 42, 0.98)';
        } else {
            navbar.classList.remove('scrolled');
            navbar.style.background = 'rgba(15, 23, 42, 0.95)';
        }
    }

    // Scroll progress bar
    if (scrollProgress) {
        const windowHeight = document.documentElement.scrollHeight - document.documentElement.clientHeight;
        const scrolled = (window.scrollY / windowHeight) * 100;
        scrollProgress.style.width = scrolled + '%';
    }
});

// Contact form submission with Formspree
const contactForm = document.querySelector('.contact-form');
if (contactForm) {
    contactForm.addEventListener('submit', async (e) => {
        e.preventDefault();
        
        // Get submit button and disable it during submission
        const submitButton = contactForm.querySelector('button[type="submit"]');
        const originalButtonText = submitButton.textContent;
        submitButton.disabled = true;
        submitButton.textContent = 'Sending...';
        
        try {
            // Create FormData object from the form
            const formData = new FormData(contactForm);
            
            // Submit to Formspree
            const response = await fetch(contactForm.action, {
                method: 'POST',
                body: formData,
                headers: {
                    'Accept': 'application/json'
                }
            });
            
            if (response.ok) {
                // Success: Show success message
                alert('Thank you for your message! I\'ll get back to you soon.');
                contactForm.reset();
            } else {
                // Error: Show error message
                const data = await response.json();
                if (data.errors) {
                    alert('Error: ' + data.errors.map(error => error.message).join(', '));
                } else {
                    alert('Sorry, there was an error sending your message. Please try again.');
                }
            }
        } catch (error) {
            // Network error
            console.error('Form submission error:', error);
            alert('Sorry, there was an error sending your message. Please check your connection and try again.');
        } finally {
            // Re-enable submit button
            submitButton.disabled = false;
            submitButton.textContent = originalButtonText;
        }
    });
}

// Animate project cards on scroll with stagger effect
const projectObserver = new IntersectionObserver((entries) => {
    entries.forEach((entry) => {
        if (entry.isIntersecting) {
            const cards = Array.from(entry.target.querySelectorAll('.project-card'));
            cards.forEach((card, index) => {
                setTimeout(() => {
                    card.style.opacity = '1';
                    card.style.transform = 'translateY(0)';
                }, index * 150);
            });
            projectObserver.unobserve(entry.target);
        }
    });
}, {
    threshold: 0.1,
    rootMargin: '0px 0px -100px 0px'
});

const projectsSection = document.querySelector('#projects');
if (projectsSection) {
    const projectsGrid = projectsSection.querySelector('.projects-grid');
    if (projectsGrid) {
        document.querySelectorAll('.project-card').forEach(card => {
            card.style.opacity = '0';
            card.style.transform = 'translateY(30px)';
            card.style.transition = 'opacity 0.6s ease, transform 0.6s ease';
        });
        projectObserver.observe(projectsGrid);
    }
}

// Animate stat items on scroll
const statObserver = new IntersectionObserver((entries) => {
    entries.forEach((entry) => {
        if (entry.isIntersecting) {
            const stats = Array.from(entry.target.querySelectorAll('.stat-item'));
            stats.forEach((stat, index) => {
                setTimeout(() => {
                    stat.style.opacity = '1';
                    stat.style.transform = 'translateY(0) scale(1)';
                }, index * 200);
            });
            statObserver.unobserve(entry.target);
        }
    });
}, {
    threshold: 0.3
});

const aboutStats = document.querySelector('.about-stats');
if (aboutStats) {
    document.querySelectorAll('.stat-item').forEach(stat => {
        stat.style.opacity = '0';
        stat.style.transform = 'translateY(20px) scale(0.9)';
        stat.style.transition = 'opacity 0.6s ease, transform 0.6s ease';
    });
    statObserver.observe(aboutStats);
}

// Add active state to navigation links based on scroll position
const sections = document.querySelectorAll('section[id]');
const navLinks = document.querySelectorAll('.nav-menu a');

window.addEventListener('scroll', () => {
    let current = '';
    
    sections.forEach(section => {
        const sectionTop = section.offsetTop;
        const sectionHeight = section.clientHeight;
        if (window.pageYOffset >= sectionTop - 200) {
            current = section.getAttribute('id');
        }
    });
    
    navLinks.forEach(link => {
        link.classList.remove('active');
        if (link.getAttribute('href') === `#${current}`) {
            link.classList.add('active');
        }
    });
});

// Project Demo Modal - Initialize when DOM is ready
function initProjectModal() {
    const modal = document.getElementById('projectModal');
    const projectFrame = document.getElementById('projectFrame');
    const modalClose = document.querySelector('.modal-close');
    
    if (!modal || !projectFrame) {
        console.error('Modal elements not found');
        return;
    }

    function openModal(demoUrl) {
        if (demoUrl) {
            projectFrame.src = demoUrl;
            modal.classList.add('show');
            document.body.style.overflow = 'hidden';
        }
    }

    function closeModal() {
        modal.classList.remove('show');
        if (projectFrame) {
            projectFrame.src = '';
        }
        document.body.style.overflow = '';
    }

    // Use event delegation for project demo links (works for clicks on link or emoji)
    document.addEventListener('click', (e) => {
        // Check if clicked element or its parent is a project-demo link
        const demoLink = e.target.closest('.project-demo');
        if (demoLink) {
            e.preventDefault();
            e.stopPropagation();
            const demoUrl = demoLink.getAttribute('data-demo');
            console.log('Opening demo:', demoUrl);
            openModal(demoUrl);
            return false;
        }
    });

    // Also attach directly to all project demo links as backup
    const projectDemoLinks = document.querySelectorAll('.project-demo');
    projectDemoLinks.forEach(link => {
        link.addEventListener('click', (e) => {
            e.preventDefault();
            e.stopPropagation();
            const demoUrl = link.getAttribute('data-demo');
            console.log('Opening demo (direct):', demoUrl);
            openModal(demoUrl);
            return false;
        });
    });

    // Close modal
    if (modalClose) {
        modalClose.addEventListener('click', () => {
            closeModal();
        });
    }

    modal.addEventListener('click', (e) => {
        if (e.target === modal) {
            closeModal();
        }
    });

    // Close modal with Escape key
    document.addEventListener('keydown', (e) => {
        if (e.key === 'Escape' && modal.classList.contains('show')) {
            closeModal();
        }
    });
}

// Initialize modal when DOM is loaded
if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', initProjectModal);
} else {
    // DOM already loaded
    initProjectModal();
}

// Add smooth parallax effect to hero section
let ticking = false;
window.addEventListener('scroll', () => {
    if (!ticking) {
        window.requestAnimationFrame(() => {
            const hero = document.querySelector('.hero');
            if (hero) {
                const scrolled = window.pageYOffset;
                const heroContent = hero.querySelector('.hero-content');
                const heroImage = hero.querySelector('.hero-image');
                
                if (heroContent && scrolled < window.innerHeight) {
                    heroContent.style.transform = `translateY(${scrolled * 0.3}px)`;
                    heroContent.style.opacity = Math.max(0.5, 1 - (scrolled / window.innerHeight) * 0.5);
                }
                
                if (heroImage && scrolled < window.innerHeight) {
                    heroImage.style.transform = `translateY(${scrolled * 0.2}px)`;
                }
            }
            ticking = false;
        });
        ticking = true;
    }
});

// Add cursor glow effect on interactive elements
document.addEventListener('DOMContentLoaded', () => {
    const interactiveElements = document.querySelectorAll('a, button, .project-card, .skill-card');
    
    interactiveElements.forEach(element => {
        element.addEventListener('mouseenter', function() {
            this.style.transition = 'all 0.3s ease';
        });
    });
});

// Add number counting animation for stats
function animateNumber(element, target, duration = 2000) {
    const start = 0;
    const increment = target / (duration / 16);
    let current = start;
    
    const timer = setInterval(() => {
        current += increment;
        if (current >= target) {
            element.textContent = target + '+';
            clearInterval(timer);
        } else {
            element.textContent = Math.floor(current) + '+';
        }
    }, 16);
}

// Observe stats and animate numbers
const numberObserver = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            const statNumber = entry.target.querySelector('.stat-number');
            if (statNumber) {
                const text = statNumber.textContent;
                const number = parseInt(text);
                if (!isNaN(number)) {
                    animateNumber(statNumber, number);
                }
            }
            numberObserver.unobserve(entry.target);
        }
    });
}, { threshold: 0.5 });

document.querySelectorAll('.stat-item').forEach(stat => {
    numberObserver.observe(stat);
});

