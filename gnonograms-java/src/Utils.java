import static java.lang.System.out;
import javax.swing.ImageIcon;
import java.util.ArrayList;
import java.util.ListIterator;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JDialog;
import javax.swing.JOptionPane;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.BorderLayout;

public class Utils
{
	static public String clueFromIntArray(int[] cs){
		//out.println("block string from cell_state_array length %d\n", cs.length);
		StringBuilder sb= new StringBuilder("");
		int count=0, blocks=0;
		boolean counting=false;

		for (int i=0; i<cs.length; i++){
			if (cs[i]==Resource.CELLSTATE_EMPTY){
				if (counting){
					sb.append(count);
					sb.append(Resource.BLOCKSEPARATOR);
					counting=false;
					count=0;
					blocks++;
				}
			}
			else if(cs[i]==Resource.CELLSTATE_FILLED){
				counting=true; count++;
			}
		}
		if (counting)	{
			sb.append(count);
			sb.append(Resource.BLOCKSEPARATOR);
			blocks++;
		}
		if (blocks==0) sb.append("0");
		else sb.setLength(sb.length() -1);

		return sb.toString();
	}

  public static int freedomFromClue(int regionSize, String clue){
    int[] blocks=blockArrayFromClue(clue);
    int count=0;
    for(int e : blocks) count+=e;
    return regionSize-count-blocks.length+1;
  }

	public static String stringFromIntArray(int[] cs)
	{
		//stdout.printf("string from cell_state_array\n");
		if (cs==null) return "";
		StringBuilder sb= new StringBuilder();
		for (int i=0; i<cs.length; i++)
		{
			sb.append(cs[i]);
			sb.append(" ");
		}
		return sb.toString();
	}

	//public static String clueFromBlockArray(int[] b)
	//{
		//StringBuilder sb=new StringBuilder("");
		//for (int block : b)
		//{
			//sb.append(block);
			//sb.append(Resource.BLOCKSEPARATOR);
		//}
		//sb.setLength(sb.length() -1);
		//return sb.toString();
	//}

  static public int[] cellStateArrayFromString(String s) throws NumberFormatException	{
		//out.println("int string: "+s);
		String[] data=removeBlankLines(s.split("[\\D\\n]",110));
		int[] csa=new int[data.length];
		for (int i=0; i<data.length; i++) {
			//out.println("Cell string"+data[i]+" as integer: "+csi);
			csa[i]=new Integer(data[i]);
		}
		return csa;
	}

	public static String[] removeBlankLines(String[] sa){
		//out.println("removeBlankLines - array length "+sa.length);
		ArrayList<String> al = new ArrayList<String>();
		int count=0;
		for (String s : sa) {
			//out.println("Length of "+s+" is "+s.length());
			if (s.length()>0) {al.add(s);count++;}
		}
    String[] result=new String[count];
    for(int i=0; i<count; i++){
			result[i]=al.get(i);
		}
		return result;
	}

	public static int[] blockArrayFromClue(String s)
	{
		//stdout.printf(@"Block array from clue $s \n");
		String[] clues=removeBlankLines(s.split("[\\D\\n]",50));

		if(clues.length==0) {
			clues=new String[1]; clues[0]="0";
		}
		int[] blocks=new int[clues.length];

		for (int i=0;i<clues.length;i++) {
			//out.println("Clue "+i+" is '"+clues[i]+"'");
			blocks[i]=Integer.parseInt(clues[i]);
			//out.println("Block "+i+" is "+blocks[i]);
		}

		return blocks;
	}

	public static boolean showConfirmDialog(String s){
		out.println("Confirm "+s);
		int result=JOptionPane.showConfirmDialog(null,s,"",JOptionPane.YES_NO_OPTION);
		return (result==JOptionPane.YES_OPTION);
	}
	public static void showWarningDialog(String s){
		out.println("Warning "+s);
		JOptionPane.showMessageDialog(null,s,"",JOptionPane.WARNING_MESSAGE);
	}
	public static void showErrorDialog(String s){
		out.println("Warning "+s);
		JOptionPane.showMessageDialog(null,s,"",JOptionPane.ERROR_MESSAGE);
	}
	public static boolean showInfoDialog(String s){
		out.println("Info "+s);
		JOptionPane.showMessageDialog(null,s,"",JOptionPane.INFORMATION_MESSAGE);
		return true;
	}
  public static JPanel okCancelPanelFactory(ActionListener listener, String okCommand){
		JButton okButton=new JButton("OK");
		okButton.setActionCommand(okCommand);
		okButton.addActionListener(listener);
		JButton cancelButton=new JButton("Cancel");
		cancelButton.setActionCommand("");
		cancelButton.addActionListener(listener);
		JPanel buttonPanel=new JPanel();
		buttonPanel.setLayout(new BorderLayout());
		buttonPanel.add(okButton, BorderLayout.LINE_START);
		buttonPanel.add(cancelButton, BorderLayout.LINE_END);
    return buttonPanel;
  }
}
