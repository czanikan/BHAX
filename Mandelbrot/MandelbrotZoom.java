import java.awt.*;
/*
 * MandelbrotHalmaz.java
 *
 * DIGIT 2005, Javat tanítok
 * Bátfai Norbert, nbatfai@inf.unideb.hu
 *
 */
/**
 * A Mandelbrot halmazt kiszámoló és kirajzoló osztály.
 * A programot módosította/kiegészítette: Czanik András
 *
 * @author Bátfai Norbert, nbatfai@inf.unideb.hu
 * @version 0.0.1
 */
public class MandelbrotZoom extends java.awt.Frame implements Runnable {

    protected double a, b, c, d;
    protected int szélesség, magasság;
    protected java.awt.image.BufferedImage kép;
    protected int iterációsHatár = 255;
    protected boolean számításFut = false;
    protected int sor = 0;
    protected static int pillanatfelvételSzámláló = 0;

	public static int x;
	public static int y;
	public static int mx;
	public static int my;

    public MandelbrotZoom(double a, double b, double c, double d,
            int szélesség, int iterációsHatár) {
        this.a = a;
        this.b = b;
        this.c = c;
        this.d = d;
        this.szélesség = szélesség;
        this.iterációsHatár = iterációsHatár;
        this.magasság = (int)(szélesség * ((d-c)/(b-a)));
        kép = new java.awt.image.BufferedImage(szélesség, magasság,
                java.awt.image.BufferedImage.TYPE_INT_RGB);
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent e) {
                setVisible(false);
                System.exit(0);
            }
        });
        addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyPressed(java.awt.event.KeyEvent e) {
                if(e.getKeyCode() == java.awt.event.KeyEvent.VK_S)
                    pillanatfelvétel();

                else if(e.getKeyCode() == java.awt.event.KeyEvent.VK_N) {
                    if(számításFut == false) {
                        MandelbrotZoom.this.iterációsHatár += 256;

                        számításFut = true;
                        new Thread(MandelbrotZoom.this).start();
                    }

                } else if(e.getKeyCode() == java.awt.event.KeyEvent.VK_M) {
                    if(számításFut == false) {
                        MandelbrotZoom.this.iterációsHatár += 10*256;

                        számításFut = true;
                        new Thread(MandelbrotZoom.this).start();
                    }
                }
            }
        });
		addMouseListener(new java.awt.event.MouseAdapter() {
			@Override
			public void mousePressed(java.awt.event.MouseEvent me) {
				x = me.getX();
				y = me.getY();
			}

			@Override
			public void mouseReleased(java.awt.event.MouseEvent me) {
				számításFut = true;
				
				double dx = (b - a) / szélesség;
    			double dy = (d - c) / magasság;

				double range = 60;

				double a = MandelbrotZoom.this.a+x*dx;
				double b = MandelbrotZoom.this.a+x*dx+range*dx;
				double c = MandelbrotZoom.this.d-y*dy-range*dy;
				double d = MandelbrotZoom.this.d-y*dy;

				MandelbrotZoom.this.a = a; 
				MandelbrotZoom.this.b = b; 
				MandelbrotZoom.this.c = c; 
				MandelbrotZoom.this.d = d; 

				new Thread(MandelbrotZoom.this).start();
			}
		});
		addMouseMotionListener(new java.awt.event.MouseMotionAdapter() {

            @Override
            public void mouseMoved(java.awt.event.MouseEvent me) {
                int mx = me.getX() - x;
				int my = mx;

				repaint();
            }
        });

        setTitle("A Mandelbrot halmaz");
        setResizable(false);
        setSize(szélesség, magasság);
        setVisible(true);

        számításFut = true;
        new Thread(this).start();
    }

    public void paint(java.awt.Graphics g) {
        g.drawImage(kép, 0, 0, this);
        if(számításFut) {
            g.setColor(java.awt.Color.RED);
            g.drawLine(0, sor, getWidth(), sor);
        }
    }

    public void update(java.awt.Graphics g) {
        paint(g);
    }

    public void pillanatfelvétel() {
        java.awt.image.BufferedImage mentKép =
                new java.awt.image.BufferedImage(szélesség, magasság,
                java.awt.image.BufferedImage.TYPE_INT_RGB);
        java.awt.Graphics g = mentKép.getGraphics();
        g.drawImage(kép, 0, 0, this);
        g.setColor(java.awt.Color.BLUE);
        g.drawString("a=" + a, 10, 15);
        g.drawString("b=" + b, 10, 30);
        g.drawString("c=" + c, 10, 45);
        g.drawString("d=" + d, 10, 60);
        g.drawString("n=" + iterációsHatár, 10, 75);
        g.dispose();

        StringBuffer sb = new StringBuffer();
        sb = sb.delete(0, sb.length());
        sb.append("MandelbrotZoom_");
        sb.append(++pillanatfelvételSzámláló);
        sb.append("_");
        sb.append(a);
        sb.append("_");
        sb.append(b);
        sb.append("_");
        sb.append(c);
        sb.append("_");
        sb.append(d);
        sb.append(".png");

        try {
            javax.imageio.ImageIO.write(mentKép, "png",
                    new java.io.File(sb.toString()));
        } catch(java.io.IOException e) {
            e.printStackTrace();
        }
    }


  
     public void run() {

        double dx = (b-a)/szélesség;
        double dy = (d-c)/magasság;
        double reC, imC, reZ, imZ, ujreZ, ujimZ;
        int rgb;
        int iteráció = 0;

        for(int j=0; j<magasság; ++j) {
            sor = j;
            for(int k=0; k<szélesség; ++k) {
                reC = a+k*dx;
                imC = d-j*dy;
                reZ = 0;
                imZ = 0;
                iteráció = 0;

                while(reZ*reZ + imZ*imZ < 4 && iteráció < iterációsHatár) {
                    ujreZ = reZ*reZ - imZ*imZ + reC;
                    ujimZ = 2*reZ*imZ + imC;
                    reZ = ujreZ;
                    imZ = ujimZ;
                    
                    ++iteráció;
                    
                }
                iteráció %= 256;
                rgb = (255-iteráció)|
                        ((255-iteráció) << 8) |
                        ((255-iteráció) << 16);
                kép.setRGB(k, j, rgb);
            }
            repaint();
        }
        számításFut = false;
    }
    public static void main(String[] args) {
        new MandelbrotZoom(-2.0, .7, -1.35, 1.35, 600, 255);
    }
}                
                
