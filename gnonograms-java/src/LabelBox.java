/*
 * LabelBox.java
 *
 * Copyright 2012 Jeremy Paul Wootten <jeremy@jeremy-laptop>
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

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.BorderFactory;

import java.awt.GridLayout;
import java.awt.ComponentOrientation;
import java.awt.Color;

class LabelBox extends JPanel{
	private static final long serialVersionUID = 1;
	GnonogramLabel[] labels;

	int no_labels;
	boolean isColumn;
	Controller control;

	public LabelBox(int no_labels, boolean isColumn, Controller control)
	{
		this.no_labels=no_labels;
		this.isColumn=isColumn;
		this.control=control;

		if (isColumn)	this.setLayout(new GridLayout(1,no_labels));
		else	this.setLayout(new GridLayout(no_labels,1));
    this.setBorder(BorderFactory.createLineBorder(Color.black));

		GnonogramLabel l;
    labels=new GnonogramLabel[no_labels];
    for (int i=0; i<no_labels; i++) {
			l=new GnonogramLabel("0", isColumn);
			labels[i]=l;
			this.add(l);
		}
	}

	public void setLabelText(int l, String text)
	{
		if (l>=no_labels || l<0) return;
		if (text==null) text="?";
		labels[l].setText(text);
//		if (isColumn) (labels[l]).setText(Utils.verticalizeString(text,Resource.BLOCKSEPARATOR));
//		else (labels[l]).setText(text);
	}

	public String getLabelText(int l)
	{
		if (l>=no_labels || l<0) return "";
		else return labels[l].getOriginalText();
		//if (isColumn) return Utils.horizontalizeString((labels[l]).getText());
		//else return (labels[l]).getText();
	}
}