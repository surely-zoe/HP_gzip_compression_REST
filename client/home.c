#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <dirent.h>
#include <ctype.h>

// Make them global

GtkWidget	*window1;
GtkWidget	*window2;
GtkWidget	*window3;
GtkWidget	*fixed1;
GtkWidget	*fixed2;
GtkWidget	*fixed3;
GtkWidget	*buttonC;
GtkWidget	*buttonD;
GtkWidget	*buttonAdd;
GtkWidget	*buttonAddFold;
GtkWidget	*buttonComp;
GtkWidget	*buttonFD;
GtkWidget 	*buttonDF;
GtkWidget	*buttonDecomp;
GtkWidget	*buttonClose1;
GtkWidget	*buttonClose2;
GtkWidget	*buttonClose3;
GtkWidget	*text1;
GtkWidget	*textbuffer1;
GtkWidget	*text2;
GtkWidget	*textbuffer2;
GtkWidget	*check1;
GtkWidget	*check2;
GtkWidget	*check3;
GtkWidget	*check4;
GtkWidget	*check5;
GtkWidget	*check6;
GtkWidget	*check7;
GtkWidget	*check8;
GtkWidget	*check9;
GtkWidget	*combo1;
GtkWidget	*label1;
GtkWidget	*label2;
GtkBuilder	*builder;

int flag=0;

void get_modes(char* modes)
{
		int i=0;
		if(gtk_toggle_button_get_active(check1))
			modes[i++]='1';
		if(gtk_toggle_button_get_active(check2))
			modes[i++]='2';
		if(gtk_toggle_button_get_active(check3))
			modes[i++]='3';
		if(gtk_toggle_button_get_active(check4))
			modes[i++]='4';
		if(gtk_toggle_button_get_active(check5))
			modes[i++]='5';
		if(gtk_toggle_button_get_active(check6))
			modes[i++]='6';
		if(gtk_toggle_button_get_active(check7))
			modes[i++]='7';
		if(gtk_toggle_button_get_active(check8))
			modes[i++]='8';
		if(gtk_toggle_button_get_active(check9))
			modes[i++]='9';
		modes[i]='\0';
}

void send_file(char* path)
{
	char command[500];
	strcpy(command,"cp -r ");
	strcat(command, path);
	strcat(command, " /home/mohit/Desktop/Project/client/send");
	system(command);
}


void checkdircomp(char* path)
{
	struct dirent *de; 
	int len;
	char *curr=(char*)malloc(sizeof(char)*150);
	char *next=(char*)malloc(sizeof(char)*150);
	strcpy(curr,path);
    DIR *dr = opendir(path); 
	
    if (dr == NULL)  
    { 
        return; 
    } 
    
    while ((de = readdir(dr)) != NULL) 
    {
			if(de->d_name[0]=='.')
				continue;
			len=strlen(de->d_name);
			if(de->d_name[len-3]=='.' && de->d_name[len-2]=='g' && de->d_name[len-1]=='z') 
			{
				flag=1;
				return;
			}
			
			memset(next,0,strlen(next));
			strcpy(next,curr);
			strcat(next,"/");
			strcat(next,de->d_name);
			checkdircomp(next);			
	}
    closedir(dr);     
    return;
}

void checkdiruncomp(char* path)
{
	struct dirent *de; 
	int len;
	char *curr=(char*)malloc(sizeof(char)*150);
	char *next=(char*)malloc(sizeof(char)*150);
	strcpy(curr,path);
    DIR *dr = opendir(path); 
	
    if (dr == NULL)  
    { 
        return; 
    } 
    
    while ((de = readdir(dr)) != NULL) 
    {
			if(de->d_name[0]=='.')
				continue;
			len=strlen(de->d_name);
			if(de->d_name[len-3]!='.' || de->d_name[len-2]!='g' || de->d_name[len-1]!='z') 
			{
				flag=1;
				return;
			}
			
			memset(next,0,strlen(next));
			strcpy(next,curr);
			strcat(next,"/");
			strcat(next,de->d_name);
			checkdiruncomp(next);			
	}
    closedir(dr);     
    return;
}

int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv); // init Gtk

//---------------------------------------------------------------------
// establish contact with xml code used to adjust widget settings
//---------------------------------------------------------------------
 
	builder = gtk_builder_new_from_file ("home.glade");
 
	window1 = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));

	g_signal_connect(window1, "destroy", G_CALLBACK(gtk_main_quit), NULL);

        gtk_builder_connect_signals(builder, NULL);

	fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
	buttonC = GTK_WIDGET(gtk_builder_get_object(builder, "buttonC"));
	buttonD = GTK_WIDGET(gtk_builder_get_object(builder, "buttonD"));
	buttonClose1 = GTK_WIDGET(gtk_builder_get_object(builder, "buttonClose1"));
	label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));

	gtk_widget_show(window1);

	gtk_main();

	return EXIT_SUCCESS;
	}

void	on_buttonC_clicked (GtkButton *b) {
	system("rm -rf receive");
	system("rm send.txt");
	system("rm -rf send");
	system("mkdir send");
	
	window2 = GTK_WIDGET(gtk_builder_get_object(builder, "window2"));

	g_signal_connect(window2, "destroy", G_CALLBACK(gtk_main_quit), NULL);

        gtk_builder_connect_signals(builder, NULL);

	fixed2 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed2"));
	buttonAddFold = GTK_WIDGET(gtk_builder_get_object(builder, "buttonAddFold"));
	buttonAdd = GTK_WIDGET(gtk_builder_get_object(builder, "buttonAdd"));
	buttonComp = GTK_WIDGET(gtk_builder_get_object(builder, "buttonComp"));
	buttonClose2 = GTK_WIDGET(gtk_builder_get_object(builder, "buttonClose2"));
	label2 = GTK_WIDGET(gtk_builder_get_object(builder, "label2"));
	check1 = GTK_WIDGET(gtk_builder_get_object(builder, "check1"));
	check2 = GTK_WIDGET(gtk_builder_get_object(builder, "check2"));
	check3 = GTK_WIDGET(gtk_builder_get_object(builder, "check3"));
	check4 = GTK_WIDGET(gtk_builder_get_object(builder, "check4"));
	check5 = GTK_WIDGET(gtk_builder_get_object(builder, "check5"));
	check6 = GTK_WIDGET(gtk_builder_get_object(builder, "check6"));
	check7 = GTK_WIDGET(gtk_builder_get_object(builder, "check7"));
	check8 = GTK_WIDGET(gtk_builder_get_object(builder, "check8"));
	check9 = GTK_WIDGET(gtk_builder_get_object(builder, "check9"));
	text1 = GTK_WIDGET(gtk_builder_get_object(builder, "text1"));
	textbuffer1 = GTK_WIDGET(gtk_builder_get_object(builder, "textbuffer1"));
	gtk_text_view_set_editable (text1, FALSE);
	gtk_text_view_set_cursor_visible (text1, FALSE);
	
	gtk_widget_show(window2);

	}
																								
	void	on_buttonAdd_clicked (GtkButton *c) {
			int len;
			char path[500];
			char *name=(char*)malloc(sizeof(char)*100);
			char *text=(char*)malloc(sizeof(char)*150);
			char *modes=(char*)malloc(sizeof(char)*15);
			strcpy(text,"file ");
			FILE *out = fopen("send.txt", "a");
			GtkWidget *dialog;
			dialog=gtk_file_chooser_dialog_new("Choose a file",GTK_WINDOW(window2),GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
			gtk_widget_show_all(dialog);
			gint resp=gtk_dialog_run(GTK_DIALOG(dialog));
			if(resp==GTK_RESPONSE_CANCEL) {
					gtk_widget_destroy(dialog);
					return;
				}
			else if(resp==GTK_RESPONSE_OK){
				strcpy(path,gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
				strcpy(name,strrchr(path, '/'));
				name=name+1;
			strcat(name," ");
			get_modes(modes);
			strcat(name, modes);
			len=strlen(name);
			gtk_text_buffer_insert_at_cursor (textbuffer1, name , len);
			gtk_text_buffer_insert_at_cursor (textbuffer1, "\n" , 1);
			strcat(text,name);
   			send_file(path);
   			fprintf(out, "%s\n", text);  
			}
			fclose(out);
			gtk_widget_destroy(dialog);
	}
	void	on_buttonAddFold_clicked (GtkButton *d) {
			int len;
			char path[500];
			char *name=(char*)malloc(sizeof(char)*100);
			char *text=(char*)malloc(sizeof(char)*150);
			char *modes=(char*)malloc(sizeof(char)*15);
			strcpy(text,"folder ");
			FILE *out = fopen("send.txt", "a");
			GtkWidget *dialog;
			dialog=gtk_file_chooser_dialog_new("Choose a folder",GTK_WINDOW(window2),GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
			gtk_widget_show_all(dialog);
			gint resp=gtk_dialog_run(GTK_DIALOG(dialog));
			if(resp==GTK_RESPONSE_CANCEL) {
					gtk_widget_destroy(dialog);
					return;
				}
			else if(resp==GTK_RESPONSE_OK){
				strcpy(path,gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
				strcpy(name,strrchr(path, '/'));
				checkdircomp(path);
				if(flag==1)
				{
					gtk_text_buffer_insert_at_cursor (textbuffer1, "Invalid folder." , 15);
					gtk_text_buffer_insert_at_cursor (textbuffer1, "\n" , 1);
					flag=0;
					
				}
				else
				{
					name=name+1;
					strcat(name," ");
					get_modes(modes);
					strcat(name,modes);
					len=strlen(name);
					gtk_text_buffer_insert_at_cursor (textbuffer1, name , len);
					gtk_text_buffer_insert_at_cursor (textbuffer1, "\n" , 1);
					strcat(text,name);
					send_file(path);
					fprintf(out, "%s\n", text);
				}
			}  
			fclose(out);	
			gtk_widget_destroy(dialog);
	}
	
	void	on_buttonComp_clicked (GtkButton *e) {
		system("./fin c");
		
		update1();
	}
	void	update1()
	{
		char line[128]; 
		int len;
		FILE *file;
		struct stat buffer;
		while((stat("/home/mohit/Desktop/Project/client/receive/file_details.txt",&buffer)))
		{
			//g_print("Waiting\n");
			sleep(10);
		}
		file = fopen("/home/mohit/Desktop/Project/client/receive/file_details.txt", "r");
		if (file==NULL)
			return;
		gtk_text_buffer_set_text (textbuffer1,"", 0);
		while ( fgets(line,sizeof(line),file)!= NULL )
		{
			len=strlen(line);
			gtk_text_buffer_insert_at_cursor (textbuffer1, line, len);
		}
		fclose(file);
	}
	
	
	
	void	on_buttonD_clicked (GtkButton *f) {
	system("rm -rf receive");
	system("rm send.txt");
	system("rm -rf send");
	system("mkdir send");
	
	window3 = GTK_WIDGET(gtk_builder_get_object(builder, "window3"));

	g_signal_connect(window3, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);

	fixed3 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed3"));
	buttonFD = GTK_WIDGET(gtk_builder_get_object(builder, "buttonFD"));
	buttonDF = GTK_WIDGET(gtk_builder_get_object(builder, "buttonDF"));
	buttonDecomp = GTK_WIDGET(gtk_builder_get_object(builder, "buttonDecomp"));
	buttonClose3 = GTK_WIDGET(gtk_builder_get_object(builder, "buttonClose3"));
	text2 = GTK_WIDGET(gtk_builder_get_object(builder, "text2"));
	textbuffer2 = GTK_WIDGET(gtk_builder_get_object(builder, "textbuffer2"));
	gtk_text_view_set_editable (text2, FALSE);
	gtk_text_view_set_cursor_visible (text2, FALSE);
	
	gtk_widget_show(window3);

	}
	
	
	void	on_buttonDecomp_clicked (GtkButton *g) {
		system("./fin d");
		update2();
	}
	
	void	update2()
	{
		char line[128]; 
		int len;
		FILE *file;
		struct stat buffer;
		while((stat("/home/mohit/Desktop/Project/client/receive/file_details.txt",&buffer)))
		{
			//g_print("Waiting\n");
			sleep(10);
		}
		file = fopen("/home/mohit/Desktop/Project/client/receive/file_details.txt", "r");
		if (file==NULL)
			return;
		gtk_text_buffer_set_text (textbuffer2,"", 0);
		while ( fgets(line,sizeof(line),file)!= NULL )
		{
			len=strlen(line);
			gtk_text_buffer_insert_at_cursor (textbuffer2, line, len);
		}
		fclose(file);
	}
	
	void	on_buttonFD_clicked (GtkButton *h) {
			char path[500];
			char *text=(char*)malloc(sizeof(char)*150);
			strcpy(text,"file ");
			char *name=(char*)malloc(sizeof(char)*100);
			FILE *out = fopen("send.txt", "a");
			GtkWidget *dialog;
			GtkFileFilter *filter = gtk_file_filter_new();
			gtk_file_filter_add_pattern (filter, "*.gz");
			dialog=gtk_file_chooser_dialog_new("Choose a compressed file",GTK_WINDOW(window3),GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
			//gtk_file_chooser_set_select_multiple (dialog, TRUE);
			gtk_file_filter_set_name (filter,".gz");
			gtk_file_chooser_add_filter (dialog,filter);
			gtk_widget_show_all(dialog);
			gint resp=gtk_dialog_run(GTK_DIALOG(dialog));
			if(resp==GTK_RESPONSE_CANCEL) {
					gtk_widget_destroy(dialog);
					return;
				}
				
			else if(resp==GTK_RESPONSE_OK){
				strcpy(path,gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
				strcpy(name,strrchr(path, '/'));
				name=name+1;
				send_file(path);
				strcat(text,name);
				fprintf(out, "%s\n", text);
			}
			fclose(out);
			int len=strlen(name);
			gtk_text_buffer_insert_at_cursor (textbuffer2, name , len);
			gtk_text_buffer_insert_at_cursor (textbuffer2, "\n" , 1);
			gtk_widget_destroy(dialog);
	}
	
	void	on_buttonDF_clicked (GtkButton *i) {
			char path[500]="";
			char *text=(char*)malloc(sizeof(char)*150);
			strcpy(text,"file ");
			char *name=(char*)malloc(sizeof(char)*100);
			FILE *out = fopen("send.txt", "a");
			GtkWidget *dialog;
			dialog=gtk_file_chooser_dialog_new("Choose a compressed folder",GTK_WINDOW(window3),GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
			gtk_widget_show_all(dialog);
			gint resp=gtk_dialog_run(GTK_DIALOG(dialog));
			if(resp==GTK_RESPONSE_CANCEL) {
					gtk_widget_destroy(dialog);
					return;
				}
			else if(resp==GTK_RESPONSE_OK){
				strcpy(path,gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
				strcpy(name,strrchr(path, '/'));
				checkdiruncomp(path);
				if(flag==1)
				{
					gtk_text_buffer_insert_at_cursor (textbuffer2, "Invalid folder." , 15);
					gtk_text_buffer_insert_at_cursor (textbuffer2, "\n" , 1);
					flag=0;
				}
				else
				{
					name=name+1;
					send_file(path);
					strcat(text,name);
					fprintf(out, "%s\n", text);
					int len=strlen(name);
					gtk_text_buffer_insert_at_cursor (textbuffer2, name , len);
					gtk_text_buffer_insert_at_cursor (textbuffer2, "\n" , 1);
				}
			}
			fclose(out);
			gtk_widget_destroy(dialog);
	}
	
	
	void	on_buttonClose1_clicked (GtkButton *j) {
		gtk_widget_destroy(window1);
	
	}
	void	on_buttonClose2_clicked (GtkButton *k) {
		gtk_widget_destroy(window2);
	
	}
	void	on_buttonClose3_clicked (GtkButton *l) {
		gtk_widget_destroy(window3);
	
	}
	
