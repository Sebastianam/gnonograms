/* Gnonograms class for Gnonograms-java
 * Main entry point.
 * Copyright 2012 Jeremy Paul Wootten <jeremywootten@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

public class Gnonograms {

  public static void main (String args[]) {
    try {
        // Set System L&F
        UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    }
    catch (UnsupportedLookAndFeelException e) {
       // handle exception
    }
    catch (ClassNotFoundException e) {
       // handle exception
    }
    catch (InstantiationException e) {
       // handle exception
    }
    catch (IllegalAccessException e) {
       // handle exception
    }
    new Controller(10,15); //default size.  TODO store user preference
  }
}

