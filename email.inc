<?php
/**
 * Implementation of hook_mail().
 */
function arduino_projects_blog_mail($key, &$message, $params)
{
	global $user;
	$language = $message['language'];
	//$language = user_preferred_language($user);
	switch ($key)
	{
		case 'arduino_projects_blog_proposal_received':
			/* initializing data */
			$query = db_select('arduino_projects_blog_proposal');
			$query->fields('arduino_projects_blog_proposal');
			$query->condition('id', $params['arduino_projects_blog_proposal_received']['proposal_id']);
			$query->range(0, 1);
			$proposal_data = $query->execute()->fetchObject();
			$user_data = user_load($params['arduino_projects_blog_proposal_received']['user_id']);
			$message['headers'] = $params['arduino_projects_blog_proposal_received']['headers'];
			$message['subject'] = t('[!site_name][Arduino Project] Your Arduino Project proposal has been received', array(
				'!site_name' => variable_get('site_name', '')
			), array(
				'language' => $language->language
			));
			$message['body'] = array(
				'body' => t('
Dear ' . $proposal_data->contributor_name . ',

Thank you for submitting proposal for the Arduino Project. The details of your proposal are as below :

Full Name: ' . $proposal_data->contributor_name . '
Email: ' . $user_data->mail . '
University/Institute: ' . $proposal_data->university . '
City: ' . $proposal_data->city . '
How did you hear about us: ' . $proposal_data->how_did_you_hear_about_us . '
Project Title: ' . $proposal_data->project_title . '
Abstract: ' . $proposal_data->abstract . '
References: ' . $proposal_data->reference . '

Your proposal is under review. You will be notified via email about the approval/disapproval within ten working days.

Best Wishes,

!site_name Team,
FOSSEE, IIT Bombay', array(
					'!site_name' => variable_get('site_name', ''),
					'!user_name' => $user_data->name
				), array(
					'language' => $language->language
				))
			);
			break;
		case 'arduino_projects_blog_proposal_approved':
			/* initializing data */
			$query = db_select('arduino_projects_blog_proposal');
			$query->fields('arduino_projects_blog_proposal');
			$query->condition('id', $params['arduino_projects_blog_proposal_approved']['proposal_id']);
			$query->range(0, 1);
			$proposal_data = $query->execute()->fetchObject();
			$user_data = user_load($params['arduino_projects_blog_proposal_approved']['user_id']);
			$url = 'https://om.fossee.in/powersystems/pssp/coding-guidelines';
			$message['headers'] = $params['arduino_projects_blog_proposal_approved']['headers'];
			$message['subject'] = t('[!site_name][Arduino Projects] Proposal for OSHW project approved', array(
				'!site_name' => variable_get('site_name', '')
			), array(
				'language' => $language->language
			));
			$message['body'] = array(
				'body' => t('
Dear ' . $proposal_data->contributor_name . ',

Congratulations! Your proposal for the Open Source Hardware Project with the following details, is approved.


Full Name: ' . $proposal_data->contributor_name . '
Email: ' . $user_data->mail . '
University/Institute: ' . $proposal_data->university . '
City: ' . $proposal_data->city . '
How did you hear about us: ' . $proposal_data->how_did_you_hear_about_us . '
Project Title: ' . $proposal_data->project_title . '
Abstract: ' . $proposal_data->abstract . '
References: ' . $proposal_data->reference . '

Please ensure that ALL the guidelines for submissions are strictly followed.

Best Wishes,

!site_name Team,
FOSSEE, IIT Bombay', array(
					'!site_name' => variable_get('site_name', ''),
					'!user_name' => $user_data->name
				), array(
					'language' => $language->language
				))
			);
			break;
		case 'arduino_projects_blog_proposal_resubmit':
			/* initializing data */
			$query = db_select('arduino_projects_blog_proposal');
			$query->fields('arduino_projects_blog_proposal');
			$query->condition('id', $params['arduino_projects_blog_proposal_resubmit']['proposal_id']);
			$query->range(0, 1);
			$proposal_data = $query->execute()->fetchObject();
			$user_data = user_load($params['arduino_projects_blog_proposal_resubmit']['user_id']);
			$message['headers'] = $params['arduino_projects_blog_proposal_resubmit']['headers'];
			$message['subject'] = t('[!site_name][Arduino Projects] Your OSHW proposal has been marked for resubmission', array(
				'!site_name' => variable_get('site_name', '')
			), array(
				'language' => $language->language
			));
			$url = l('here', '/arduino-projects/my-proposals');
			$message['body'] = array(
				'body' => t('
Dear ' . $proposal_data->contributor_name . ',

We like to inform you that your Open Source Hardware Project proposal with the following details

Full Name: ' . $proposal_data->contributor_name . '
Email: ' . $user_data->mail . '
University/Institute: ' . $proposal_data->university . '
City: ' . $proposal_data->city . '
How did you hear about us: ' . $proposal_data->how_did_you_hear_about_us . '
Project Title: ' . $proposal_data->project_title . '
Abstract: ' . $proposal_data->abstract . '
References: ' . $proposal_data->reference . '

must be resubmitted after making changes considering the following reviewer’s comments.

Comment: ' . $proposal_data->resubmit_comment . '

Failing to do so within 2 weeks from today, will automatically lead to disapproval of the proposal. Please note that once you resubmit the proposal, it will be reviewed again.

You may edit and resubmit you proposal' . $url . '.

Thank you for participating in the Open Source Hardware Project and looking forward to your response.

Best Wishes,

!site_name Team,
FOSSEE, IIT Bombay', array(
					'!site_name' => variable_get('site_name', ''),
					'!user_name' => $user_data->name
				), array(
					'language' => $language->language
				))
			);
			break;
		case 'arduino_projects_blog_proposal_disapproved':
			/* initializing data */
			$query = db_select('arduino_projects_blog_proposal');
			$query->fields('arduino_projects_blog_proposal');
			$query->condition('id', $params['arduino_projects_blog_proposal_disapproved']['proposal_id']);
			$query->range(0, 1);
			$proposal_data = $query->execute()->fetchObject();
			$user_data = user_load($params['arduino_projects_blog_proposal_disapproved']['user_id']);
			$message['headers'] = $params['arduino_projects_blog_proposal_disapproved']['headers'];
			$message['subject'] = t('[!site_name][Arduino Projects] Your OSHW proposal has been disapproved', array(
				'!site_name' => variable_get('site_name', '')
			), array(
				'language' => $language->language
			));
			$message['body'] = array(
				'body' => t('
Dear ' . $proposal_data->contributor_name . ',

We regret to inform you that your Open Source Hardware Project proposal with the following details have been disapproved.

Full Name: ' . $proposal_data->contributor_name . '
Email: ' . $user_data->mail . '
University/Institute: ' . $proposal_data->university . '
City: ' . $proposal_data->city . '
How did you hear about us: ' . $proposal_data->how_did_you_hear_about_us . '
Project Title: ' . $proposal_data->project_title . '
Abstract: ' . $proposal_data->abstract . '
References: ' . $proposal_data->reference . '

Reason(s) / Feedback: ' . $proposal_data->dissapproval_reason . '

Please note that any files that were uploaded along with the proposal form will be deleted from all our database(s).

Thank you for participating in the  Open Source Hardware Project. You are welcome to submit a new proposal.

Best Wishes,

!site_name Team,
FOSSEE, IIT Bombay', array(
					'!site_name' => variable_get('site_name', ''),
					'!user_name' => $user_data->name
				), array(
					'language' => $language->language
				))
			);
			break;
		case 'arduino_projects_blog_proposal_resubmit_ack':
			/* initializing data */
			$query = db_select('arduino_projects_blog_proposal');
			$query->fields('arduino_projects_blog_proposal');
			$query->condition('id', $params['arduino_projects_blog_proposal_resubmit_ack']['proposal_id']);
			$query->range(0, 1);
			$proposal_data = $query->execute()->fetchObject();
			$user_data = user_load($params['arduino_projects_blog_proposal_resubmit_ack']['user_id']);
			$message['headers'] = $params['arduino_projects_blog_proposal_resubmit_ack']['headers'];
			$message['subject'] = t('[!site_name][Arduino Projects] Proposal Resubmission for OSHW project is successful', array(
				'!site_name' => variable_get('site_name', '')
			), array(
				'language' => $language->language
			));
			$url = l('here', '/arduino-projects/my-proposals');
			$message['body'] = array(
				'body' => t('
Dear ' . $proposal_data->contributor_name . ',

Thank you for your re-submission. We have received your resubmitted proposal for the Open Source Hardware Project with the following details:

Full Name: ' . $proposal_data->contributor_name . '
Email: ' . $user_data->mail . '
University/Institute: ' . $proposal_data->university . '
City: ' . $proposal_data->city . '
How did you hear about us: ' . $proposal_data->how_did_you_hear_about_us . '
Project Title: ' . $proposal_data->project_title . '
Abstract: ' . $proposal_data->abstract . '
References: ' . $proposal_data->reference . '

Your proposal is under review. You will receive an email as soon as it has been reviewed. 

Best Wishes,

!site_name Team,
FOSSEE, IIT Bombay', array(
					'!site_name' => variable_get('site_name', ''),
					'!user_name' => $user_data->name
				), array(
					'language' => $language->language
				))
			);
			break;
		case 'arduino_projects_blog_proposal_completed':
			/* initializing data */
			$query = db_select('arduino_projects_blog_proposal');
			$query->fields('arduino_projects_blog_proposal');
			$query->condition('id', $params['arduino_projects_blog_proposal_completed']['proposal_id']);
			$query->range(0, 1);
			$proposal_data = $query->execute()->fetchObject();
			$user_data = user_load($params['arduino_projects_blog_proposal_completed']['user_id']);
			if ($proposal_data->project_guide_name == "NULL" || $proposal_data->project_guide_name == "")
			{
				$project_guide_name = "Not Entered";
			} //$proposal_data->project_guide_name == NULL
			else
			{
				$project_guide_name = $proposal_data->project_guide_name;
			}
			if ($proposal_data->project_guide_email_id == "NULL" || $proposal_data->project_guide_email_id == "")
			{
				$project_guide_email_id = "Not Entered";
			} //$proposal_data->project_guide_email_id == NULL
			else
			{
				$project_guide_email_id = $proposal_data->project_guide_email_id;
			}
			$message['headers'] = $params['arduino_projects_blog_proposal_completed']['headers'];
			$message['subject'] = t('[!site_name][Arduino Project Project] Your OpenModelica Arduino Project Project proposal has been completed', array(
				'!site_name' => variable_get('site_name', '')
			), array(
				'language' => $language->language
			));
			$message['body'] = array(
				'body' => t('
Dear ' . $proposal_data->contributor_name . ',

Your simulation and abstract for Arduino Project at FOSSEE on the following process have been published successfully.


Full Name : ' . $proposal_data->contributor_name . '
Project Title  : ' . $proposal_data->project_title . '

Kindly access this link to download the same.
https://om.fossee.in/powersystems/pssp/completed-pssp


Thank you for participating in the Arduino Project Project. You are welcome to propose a new proposal.


Best Wishes,

!site_name Team,
FOSSEE, IIT Bombay', array(
					'!site_name' => variable_get('site_name', ''),
					'!user_name' => $user_data->name
				), array(
					'language' => $language->language
				))
			);
			break;
		case 'arduino_projects_blog_proposal_deleted':
			/* initializing data */
			$query = db_select('arduino_projects_blog_proposal');
			$query->fields('arduino_projects_blog_proposal');
			$query->condition('id', $params['arduino_projects_blog_proposal_deleted']['proposal_id']);
			$query->range(0, 1);
			$proposal_data = $query->execute()->fetchObject();
			$user_data = user_load($params['arduino_projects_blog_proposal_deleted']['user_id']);
			
			if ($proposal_data->project_guide_name == "NULL" || $proposal_data->project_guide_name == "")
			{
				$project_guide_name = "Not Entered";
			} //$proposal_data->project_guide_name == NULL
			else
			{
				$project_guide_name = $proposal_data->project_guide_name;
			}
			if ($proposal_data->project_guide_email_id == "NULL" || $proposal_data->project_guide_email_id == "")
			{
				$project_guide_email_id = "Not Entered";
			} //$proposal_data->project_guide_email_id == NULL
			else
			{
				$project_guide_email_id = $proposal_data->project_guide_email_id;
			}
			$message['headers'] = $params['arduino_projects_blog_proposal_deleted']['headers'];
			$message['subject'] = t('[!site_name][Arduino Project Project] Your OpenModelica Arduino Project Project proposal has been deleted', array(
				'!site_name' => variable_get('site_name', '')
			), array(
				'language' => $language->language
			));
			$message['body'] = array(
				'body' => t('
Dear ' . $proposal_data->contributor_name . ',

Your  Arduino Project proposal with the following details has been deleted:

Full Name : ' . $proposal_data->contributor_name . '
Email : ' . $user_data->mail . '
University/Institute : ' . $proposal_data->university . '
City : ' . $proposal_data->city . '

Project Title  : ' . $proposal_data->project_title . '
Abstract: ' . $proposal_data->abstract .'



You can propose a new Arduino project.

Best Wishes,

!site_name Team,
FOSSEE, IIT Bombay', array(
					'!site_name' => variable_get('site_name', ''),
					'!user_name' => $user_data->name
				), array(
					'language' => $language->language
				))
			);
			break;
		/**************************************************************/
		case 'abstract_uploaded':
			// $solution_q = db_query("SELECT * FROM {arduino_projects_blog_solution} WHERE id = %d LIMIT 1", $params['abstract_uploaded']['solution_id']);
			$query = db_select('arduino_projects_blog_proposal');
			$query->fields('arduino_projects_blog_proposal');
			$query->condition('id', $params['abstract_uploaded']['proposal_id']);
			$query->range(0, 1);
			$proposal_data = $query->execute()->fetchObject();
			
			$user_data = user_load($params['abstract_uploaded']['user_id']);
			$message['subject'] = t('[!site_name][Arduino Project Project] You have uploaded OpenModelica model and abstract', array(
				'!site_name' => variable_get('site_name', '')
			), array(
				'language' => $language->language
			));
			$message['headers'] = $params['abstract_uploaded']['headers'];
			$message['body'] = array(
				'body' => t('
Dear ' . $proposal_data->contributor_name . ',

You have successfully uploaded your simulation and abstract for Arduino Project with the following details.

Full Name : ' . $proposal_data->contributor_name . '
Email : ' . $user_data->mail . '
University/Institute : ' . $proposal_data->university . '
City : ' . $proposal_data->city . '

Project Title  : ' . $proposal_data->project_title . '
Abstract: ' . $proposal_data->abstract .'

You shall be notified via email after the model and abstract are reviewed and approved / disapproved. This may take upto 30 working days.

Best Wishes,

!site_name Team,
FOSSEE, IIT Bombay', array(
					'!site_name' => variable_get('site_name', ''),
					'!user_name' => $user_data->name
				), array(
					'language' => $language->language
				))
			);
			break;
		case 'standard':
			$message['subject'] = $params['standard']['subject'];
			$message['body'] = $params['standard']['body'];
			$message['headers'] = $params['standard']['headers'];
			break;
	} //$key
}
